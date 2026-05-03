# Emergency SOS Web Application

Create a full-stack Emergency SOS Web Application with a Vite + React frontend and a Node.js + Express backend, integrating real-time location tracking, audio/video recording, voice keyword detection, and Twilio SMS alerts.

## User Review Required
> [!IMPORTANT]
> The application requires external services (Firebase, Twilio) for full functionality. Please review the open questions below to clarify the approach.

## Open Questions
> [!WARNING]
> 1. **Database Selection**: Would you prefer MongoDB or Firebase for the database? (You have a FIREBASE_SETUP.md file open in another directory, so I assume Firebase might be preferred, but please confirm).
> 2. **External APIs**: Do you have a Twilio account and Firebase/MongoDB project ready with their respective API keys, or should I mock the Twilio SMS functionality and database for local development purposes?
> 3. **Styling**: Our guidelines recommend Vanilla CSS for a premium, dynamic design. Is Vanilla CSS okay, or do you explicitly require a framework like Tailwind CSS?

## Proposed Changes

### Backend Setup (Node.js + Express)
We will set up a robust backend to handle real-time WebSockets and API requests.
- **Dependencies**: `express`, `cors`, `dotenv`, `socket.io`, `twilio`, and the DB SDK (`firebase-admin` or `mongoose`).
- **Core Architecture**:
  - `server/index.js`: Main Express and Socket.io server entry point.
  - `server/routes/api.js`: REST endpoints for user registration and alert triggers.
  - `server/controllers/alertController.js`: Logic to handle incoming SOS alerts and dispatch Twilio SMS.
  - `server/sockets/locationHandler.js`: Socket.io event handlers for live location and media chunk updates.

### Frontend Setup (Vite + React)
A mobile-first, high-contrast Red theme UI with a premium look, featuring glassmorphism and subtle micro-animations to feel responsive.
- **Dependencies**: `react`, `react-router-dom`, `socket.io-client`.
- **Core Architecture**:
  - `client/src/index.css`: Core design system with vibrant red tones, glassmorphism, and dynamic animations.
  - `client/src/App.jsx`: Main routing setup.
  - `client/src/pages/Home.jsx`: The main dashboard with the giant SOS button and status indicators.
  - `client/src/pages/Setup.jsx`: User onboarding for name and emergency contacts.
  - `client/src/hooks/useSpeechRecognition.js`: Custom hook to interface with Web Speech API for background distress keyword detection.
  - `client/src/hooks/useMediaCapture.js`: Custom hook for MediaRecorder API to capture 10-second chunks of evidence.
  - `client/src/hooks/useGeolocation.js`: Custom hook for continuous location tracking.

### Feature Implementations
1. **SOS Button & UI**: Large, pulsating, premium red button in `Home.jsx` that aggregates triggers from `useGeolocation` and `useMediaCapture`.
2. **Smart Keyword Detection**: `useSpeechRecognition` will run continually. When "help", "save me", or "emergency" are detected, it acts as a virtual click on the SOS button.
3. **Live Location Sharing**: Once SOS is triggered, `useGeolocation` sends coordinates every 5-10 seconds to the backend via `socket.io-client`.
4. **Evidence Capture**: On SOS trigger, `useMediaCapture` records audio/video chunks and sends blobs to the backend.
5. **Emergency Alerts**: Backend calls Twilio API to send SMS with a live location link to registered contacts.
6. **Offline Fallback**: The client will attempt to use a direct SMS intent (`sms:?body=...`) if `navigator.onLine` is false, and queue data in `localStorage` to sync later.

## Verification Plan

### Automated Tests
- N/A for initial setup (focusing on manual functionality verification).

### Manual Verification
- Start the Vite dev server and Node backend.
- Go through the `Setup` flow to add a profile and emergency contact.
- Navigate to the `Home` page.
- **Test 1**: Click the SOS button manually and observe network traffic for location sockets and Twilio API triggers.
- **Test 2**: Say "help" near the microphone and ensure the SOS flow triggers automatically.
- **Test 3**: Disable network connection and verify the offline fallback UI appears and SMS intents are formed.
