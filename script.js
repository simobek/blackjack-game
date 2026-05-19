async function startGame() {
    const infinite = document.getElementById('infinite-deck').checked;
    
    const response = await fetch('/api/start', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ decks: 2, infinite: infinite })
    });
    
    if(response.ok) {
        document.getElementById('setup-panel').classList.add('hidden');
        document.getElementById('game-area').classList.remove('hidden');
        const data = await response.json();
        updateUI(data);
    }
}

async function hit() {
    const response = await fetch('/api/hit', { method: 'POST' });
    if(response.ok) {
        const data = await response.json();
        updateUI(data);
    }
}

async function stand() {
    const response = await fetch('/api/stand', { method: 'POST' });
    if(response.ok) {
        const data = await response.json();
        updateUI(data);
    }
}

function updateUI(state) {
    renderHand('player-cards', state.playerHand);
    renderHand('dealer-cards', state.dealerHand);
    
    document.getElementById('player-score').textContent = `(Score: ${state.playerScore})`;
    document.getElementById('dealer-score').textContent = state.dealerScore > 0 ? `(Score: ${state.dealerScore})` : '';

    const msg = document.getElementById('message-area');
    msg.textContent = state.message || "";
    
    const rec = document.getElementById('recommendation-area');
    rec.textContent = state.recommendation ? `Tip: ${state.recommendation}` : "";

    const gameOver = state.gameOver;
    document.getElementById('btn-hit').disabled = gameOver;
    document.getElementById('btn-stand').disabled = gameOver;
    
    if(gameOver) {
        document.getElementById('setup-panel').classList.remove('hidden'); // Allow new game
    }
}

function renderHand(elementId, cards) {
    const container = document.getElementById(elementId);
    container.innerHTML = '';
    
    cards.forEach(val => {
        const cardDiv = document.createElement('div');
        cardDiv.className = 'card';
        cardDiv.textContent = val === 0 ? '?' : val;
        container.appendChild(cardDiv);
    });
}
