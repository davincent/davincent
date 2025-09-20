import React from 'react';
import Map from './Map'; // Make sure the path to your Map component is correct
import './App.css'; // You might have a default App.css

function App() {
  return (
    <div className="App" style={{ height: '100vh', display: 'flex' }}>
      <nav className="App-nav">
        <h1>Foxhole Map</h1>
        <ul>
          <li><button>Tool 1</button></li>
          <li><button>Tool 2</button></li>
          <li><button>Tool 3</button></li>
        </ul>
      </nav>
      <main style={{ flex: 1 }}>
        <Map /> {/* This line renders your Map component */}
      </main>
    </div>
  );
}

export default App;