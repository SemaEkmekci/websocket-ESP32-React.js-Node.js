import React, { useEffect, useState } from 'react';

const WebSocketComponent = () => {
  const [messages, setMessages] = useState([]);
  
  useEffect(() => {
    const ws = new WebSocket('ws://localhost:8080'); // WebSocket sunucusunun URL'si

    ws.onopen = () => {
      console.log('Connected to WebSocket server');
    };

    ws.onmessage = (event) => {
      // Gelen veriyi işleme
      if (typeof event.data === 'string') {
        setMessages((prevMessages) => [...prevMessages, event.data]);
      } else {
        const reader = new FileReader();
        reader.onload = () => {
          setMessages((prevMessages) => [...prevMessages, reader.result]);
        };
        reader.readAsText(event.data);
      }
    };

    ws.onclose = () => {
      console.log('Disconnected from WebSocket server');
    };

    return () => {
      ws.close();
    };
  }, []);

  return (
    <div>
      <h1>WebSocket Messages</h1>
      <ul>
        {messages.map((message, index) => (
          <li key={index}>{message}</li>
        ))}
      </ul>
    </div>
  );
};

export default WebSocketComponent;
