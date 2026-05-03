import React, { useState, useEffect } from 'react';
import { User, Phone, Save, Plus, Trash2 } from 'lucide-react';
import { useNavigate } from 'react-router-dom';
// import { db } from '../firebase'; // Skipping direct DB import for now to prevent crash without keys
// import { collection, addDoc } from 'firebase/firestore';

export default function Setup() {
  const [name, setName] = useState('');
  const [contacts, setContacts] = useState(['']);
  const [saving, setSaving] = useState(false);
  const navigate = useNavigate();

  useEffect(() => {
    const savedName = localStorage.getItem('sos_name');
    const savedContacts = localStorage.getItem('sos_contacts');
    if (savedName) setName(savedName);
    if (savedContacts) {
      try {
        const parsed = JSON.parse(savedContacts);
        if (parsed.length > 0) setContacts(parsed);
      } catch (e) {
        // ignore
      }
    }
  }, []);

  const handleContactChange = (index, value) => {
    const newContacts = [...contacts];
    newContacts[index] = value;
    setContacts(newContacts);
  };

  const addContact = () => {
    setContacts([...contacts, '']);
  };

  const removeContact = (index) => {
    const newContacts = contacts.filter((_, i) => i !== index);
    if (newContacts.length === 0) newContacts.push('');
    setContacts(newContacts);
  };

  const handleSave = async (e) => {
    e.preventDefault();
    setSaving(true);
    
    // Filter out empty contacts
    const validContacts = contacts.filter(c => c.trim() !== '');
    
    // Save locally for offline support
    localStorage.setItem('sos_name', name);
    localStorage.setItem('sos_contacts', JSON.stringify(validContacts));

    // Optional: Save to Firebase if configured
    /*
    try {
      await addDoc(collection(db, 'users'), {
        name,
        contacts: validContacts,
        updatedAt: new Date()
      });
    } catch (error) {
      console.error("Firebase sync failed", error);
    }
    */
    
    setTimeout(() => {
      setSaving(false);
      navigate('/');
    }, 600);
  };

  return (
    <div className="glass-panel" style={{ animation: 'fade-in 0.5s ease-out' }}>
      <h1>Profile Setup</h1>
      <p style={{ marginBottom: '2rem' }}>Configure your emergency details so we can alert the right people.</p>
      
      <form onSubmit={handleSave}>
        <div className="input-group">
          <label>Your Full Name</label>
          <div style={{ position: 'relative' }}>
            <User size={20} style={{ position: 'absolute', top: '16px', left: '16px', color: '#a09090' }} />
            <input 
              type="text" 
              required
              value={name}
              onChange={(e) => setName(e.target.value)}
              placeholder="e.g. Jane Doe" 
              style={{ paddingLeft: '3rem', width: '100%' }}
            />
          </div>
        </div>

        <div className="input-group" style={{ marginTop: '2rem' }}>
          <label>Emergency Contacts</label>
          {contacts.map((contact, index) => (
            <div key={index} style={{ display: 'flex', gap: '0.5rem', marginBottom: '0.5rem' }}>
              <div style={{ position: 'relative', flex: 1 }}>
                <Phone size={20} style={{ position: 'absolute', top: '16px', left: '16px', color: '#a09090' }} />
                <input 
                  type="tel" 
                  required={index === 0}
                  value={contact}
                  onChange={(e) => handleContactChange(index, e.target.value)}
                  placeholder="+1 (555) 000-0000" 
                  style={{ paddingLeft: '3rem', width: '100%' }}
                />
              </div>
              <button 
                type="button" 
                onClick={() => removeContact(index)}
                style={{ 
                  background: 'rgba(255, 42, 42, 0.1)', 
                  border: 'none', 
                  borderRadius: '12px', 
                  width: '56px', 
                  color: 'var(--red-primary)',
                  cursor: 'pointer'
                }}
              >
                <Trash2 size={20} style={{ margin: '0 auto' }} />
              </button>
            </div>
          ))}
          
          <button 
            type="button" 
            onClick={addContact}
            className="btn btn-secondary" 
            style={{ alignSelf: 'flex-start', marginTop: '0.5rem', fontSize: '0.875rem', padding: '0.5rem 1rem' }}
          >
            <Plus size={16} /> Add Another
          </button>
        </div>

        <button 
          type="submit" 
          className="btn btn-primary" 
          style={{ width: '100%', marginTop: '2rem' }}
          disabled={saving}
        >
          {saving ? 'Saving...' : <><Save size={20} /> Save Configuration</>}
        </button>
      </form>
    </div>
  );
}
