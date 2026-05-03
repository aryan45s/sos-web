import { useState, useEffect, useCallback, useRef } from 'react';

export default function useSpeechRecognition(onKeywordDetected) {
  const [isListening, setIsListening] = useState(false);
  const [error, setError] = useState(null);
  const recognitionRef = useRef(null);

  const startListening = useCallback(() => {
    const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
    if (!SpeechRecognition) {
      setError('Speech Recognition API is not supported in this browser.');
      return;
    }

    try {
      const recognition = new SpeechRecognition();
      recognition.continuous = true;
      recognition.interimResults = true;
      recognition.lang = 'en-US';

      recognition.onresult = (event) => {
        const current = event.resultIndex;
        const transcript = event.results[current][0].transcript.toLowerCase();
        
        const keywords = ['help', 'emergency', 'save me', 'sos'];
        const detected = keywords.some(keyword => transcript.includes(keyword));
        
        if (detected) {
          onKeywordDetected(transcript);
        }
      };

      recognition.onerror = (event) => {
        if (event.error !== 'no-speech') {
          setError(`Speech recognition error: ${event.error}`);
          setIsListening(false);
        }
      };

      recognition.onend = () => {
        // Auto-restart if we are supposed to be listening
        if (isListening) {
          try {
            recognition.start();
          } catch (e) {
            // Ignore if already started
          }
        }
      };

      recognition.start();
      recognitionRef.current = recognition;
      setIsListening(true);
      setError(null);
    } catch (err) {
      setError(err.message);
    }
  }, [isListening, onKeywordDetected]);

  const stopListening = useCallback(() => {
    setIsListening(false);
    if (recognitionRef.current) {
      recognitionRef.current.stop();
    }
  }, []);

  useEffect(() => {
    return () => stopListening();
  }, [stopListening]);

  return { isListening, error, startListening, stopListening };
}
