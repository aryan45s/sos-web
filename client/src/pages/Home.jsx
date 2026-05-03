import React, { useState, useEffect, useCallback, useRef } from 'react';
import { Mic, MapPin, Video, AlertTriangle, ShieldCheck } from 'lucide-react';
import useGeolocation from '../hooks/useGeolocation';
import useSpeechRecognition from '../hooks/useSpeechRecognition';
import useMediaCapture from '../hooks/useMediaCapture';

export default function Home() {
  const [sosActive, setSosActive] = useState(false);
  const [status, setStatus] = useState('System ready. Voice detection active.');
  
  // Contacts and profile
  const savedName = localStorage.getItem('sos_name') || 'Unknown User';
  const savedContacts = JSON.parse(localStorage.getItem('sos_contacts') || '[]');

  // Hooks
  const { location, startTracking, stopTracking } = useGeolocation();
  
  const handleVoiceTrigger = useCallback((transcript) => {
    if (!sosActive) {
      console.log(`Voice triggered: ${transcript}`);
      triggerSOS();
    }
  }, [sosActive]);

  const { isListening, startListening, stopListening } = useSpeechRecognition(handleVoiceTrigger);
  
  const handleMediaChunk = useCallback(async (blob) => {
    console.log("Captured evidence chunk:", blob.size, "bytes");
    
    // Create a URL for the blob and trigger an automatic download to the user's computer
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.style.display = 'none';
    a.href = url;
    a.download = `sos_evidence_${new Date().toISOString().replace(/[:.]/g, '-')}.webm`;
    document.body.appendChild(a);
    a.click();
    
    // Clean up
    setTimeout(() => {
      document.body.removeChild(a);
      URL.revokeObjectURL(url);
    }, 100);

    // In the future, you can also upload 'blob' to Firebase Storage here:
    // const storageRef = ref(storage, `evidence/${Date.now()}.webm`);
    // await uploadBytes(storageRef, blob);
  }, []);

  const { isRecording, startRecording, stopRecording } = useMediaCapture(handleMediaChunk);

  // Auto-start listening on mount
  useEffect(() => {
    startListening();
    return () => {
      stopListening();
      stopTracking();
      stopRecording();
    };
  }, []);

  // Sync location to backend if active
  useEffect(() => {
    if (sosActive && location) {
      // In a real app with Firebase keys, we'd update Firestore
      console.log('Syncing location to DB:', location);
    }
  }, [sosActive, location]);

  const triggerSOS = async () => {
    if (sosActive) return; // Prevent double trigger
    
    if (savedContacts.length === 0) {
      alert("Please configure your emergency contacts in Setup first!");
      return;
    }

    setSosActive(true);
    setStatus('SOS TRIGGERED! Alerting contacts...');
    
    // Start tracking & recording
    startTracking();
    startRecording();

    // Generate SMS Link logic
    const baseLoc = location ? `https://maps.google.com/?q=${location.lat},${location.lng}` : "Location tracking...";
    const message = `🚨 SOS ALERT from ${savedName}! 🚨\nI need help immediately.\n\nLive Location: ${baseLoc}`;

    if (!navigator.onLine) {
      // Offline fallback: Use native SMS intent
      setStatus('Offline! Launching SMS app...');
      const phoneList = savedContacts.join(',');
      window.location.href = `sms:${phoneList}?body=${encodeURIComponent(message)}`;
    } else {
      // Online: Try backend Twilio API
      try {
        const response = await fetch('http://localhost:5000/api/alert', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({
            name: savedName,
            contacts: savedContacts,
            location: location || { lat: 0, lng: 0 },
            message
          })
        });
        
        if (response.ok) {
          setStatus('Alerts dispatched to contacts.');
        } else {
          const errData = await response.json();
          throw new Error(errData.details || 'Backend failed');
        }
      } catch (err) {
        console.error("Alert failed:", err);
        // If it's a TypeError, it means the server is offline/unreachable
        if (err.name === 'TypeError') {
          setStatus('Backend offline! Launching SMS app...');
          const phoneList = savedContacts.join(',');
          window.location.href = `sms:${phoneList}?body=${encodeURIComponent(message)}`;
        } else {
          // If it's a Twilio error, show it to the user so they know what went wrong
          setStatus(`Twilio Error: ${err.message}`);
          setTimeout(() => cancelSOS(), 5000);
        }
      }
    }
  };

  const cancelSOS = () => {
    setSosActive(false);
    setStatus('SOS Cancelled. System returning to standby.');
    stopTracking();
    stopRecording();
    setTimeout(() => setStatus('System ready. Voice detection active.'), 3000);
  };

  return (
    <div className="app-container" style={{ alignItems: 'center' }}>
      <header className="top-nav" style={{ width: '100%' }}>
        <div className="logo">
          {sosActive ? <AlertTriangle className="logo-icon danger" size={24} /> : <ShieldCheck className="logo-icon" style={{ color: 'var(--green-status)' }} size={24} />}
          <span>RescueNode</span>
        </div>
        <div style={{ fontSize: '0.8rem', color: 'var(--text-muted)' }}>
          {savedContacts.length} Contacts
        </div>
      </header>

      <div style={{ textAlign: 'center', marginBottom: '1rem', height: '20px', color: sosActive ? 'var(--red-primary)' : 'var(--text-muted)' }}>
        {status}
      </div>

      <div className="sos-container">
        {sosActive && (
          <>
            <div className="ripple"></div>
            <div className="ripple"></div>
            <div className="ripple"></div>
          </>
        )}
        <button 
          className={`sos-button ${sosActive ? 'active' : ''}`}
          onClick={sosActive ? cancelSOS : triggerSOS}
        >
          {sosActive ? 'STOP' : 'SOS'}
        </button>
      </div>

      <div className="status-bar" style={{ width: '100%' }}>
        <div className="status-item">
          <div className={`status-icon ${sosActive ? 'active' : 'warning'}`}>
            <MapPin size={20} />
          </div>
          <div className="status-text">
            <div className="status-title">Location Tracking</div>
            <div className="status-desc">
              {sosActive 
                ? (location ? `Lat: ${location.lat.toFixed(4)}, Lng: ${location.lng.toFixed(4)}` : 'Acquiring GPS...')
                : 'Standby'
              }
            </div>
          </div>
        </div>

        <div className="status-item">
          <div className={`status-icon ${isListening ? 'active' : ''}`}>
            <Mic size={20} />
          </div>
          <div className="status-text">
            <div className="status-title">Voice Detection</div>
            <div className="status-desc">{isListening ? 'Listening for "help", "emergency"' : 'Disabled'}</div>
          </div>
        </div>

        <div className="status-item">
          <div className={`status-icon ${isRecording ? 'danger' : ''}`}>
            <Video size={20} />
          </div>
          <div className="status-text">
            <div className="status-title">Evidence Capture</div>
            <div className="status-desc">{isRecording ? 'Recording audio/video chunks...' : 'Standby'}</div>
          </div>
        </div>
      </div>
    </div>
  );
}
