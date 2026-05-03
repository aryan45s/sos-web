const express = require('express');
const cors = require('cors');
const dotenv = require('dotenv');
const twilio = require('twilio');

dotenv.config();

const app = express();
app.use(cors());
app.use(express.json());

// Twilio Setup
const accountSid = process.env.TWILIO_ACCOUNT_SID;
const authToken = process.env.TWILIO_AUTH_TOKEN;
const twilioPhone = process.env.TWILIO_PHONE_NUMBER;
const client = accountSid && authToken ? twilio(accountSid, authToken) : null;

app.post('/api/alert', async (req, res) => {
  try {
    const { contacts, name, location, message } = req.body;

    if (!contacts || !Array.isArray(contacts) || contacts.length === 0) {
      return res.status(400).json({ error: 'No contacts provided' });
    }

    if (!client) {
      console.warn('Twilio client not configured. Mocking SMS send.');
      return res.status(200).json({ success: true, mocked: true, message: 'Alert mocked (Twilio not configured).' });
    }

    const defaultMessage = `🚨 SOS ALERT from ${name}! 🚨\nI need help immediately.\n\nLocation: https://maps.google.com/?q=${location.lat},${location.lng}`;
    const smsBody = message || defaultMessage;

    // Send SMS to all contacts concurrently
    const sendPromises = contacts.map(contact => 
      client.messages.create({
        body: smsBody,
        from: twilioPhone,
        to: contact
      })
    );

    await Promise.all(sendPromises);

    res.status(200).json({ success: true, message: 'Alert sent successfully' });
  } catch (error) {
    console.error('Error sending alert:', error);
    res.status(500).json({ error: 'Failed to send alert', details: error.message });
  }
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`SOS Backend running on port ${PORT}`);
});
