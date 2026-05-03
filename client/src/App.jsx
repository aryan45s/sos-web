import React from 'react';
import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';
import { ShieldAlert, Settings } from 'lucide-react';
import Home from './pages/Home';
import Setup from './pages/Setup';

function App() {
  return (
    <BrowserRouter>
      <div className="app-container">
        <header className="top-nav">
          <Link to="/" className="logo">
            <ShieldAlert className="logo-icon" size={24} />
            <span>RescueNode</span>
          </Link>
          <Link to="/setup" className="nav-link">
            <Settings size={20} />
            <span>Setup</span>
          </Link>
        </header>
        
        <main style={{ flex: 1 }}>
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/setup" element={<Setup />} />
          </Routes>
        </main>
      </div>
    </BrowserRouter>
  );
}

export default App;
