document.addEventListener('DOMContentLoaded', () => {
    let totalSeconds = 600; // 10 minuti
    let timerInterval;

    // Variabile per salvare le risposte
    const userAnswers = {
        open: {},
        closed: {}
    };

    // Timer
    function updateTimer() {
        const minutes = Math.floor(totalSeconds / 60);
        const seconds = totalSeconds % 60;
        document.getElementById('time').textContent = `${minutes}:${seconds < 10 ? '0' : ''}${seconds}`;
        totalSeconds--;

        if (totalSeconds < 0) {
            completeTest();
        }
    }

    // Completa il test
    function completeTest() {
        clearInterval(timerInterval);

        // Nascondi le sezioni
        document.getElementById('openQuestionsSection').classList.add('d-none');
        document.getElementById('closedQuestionsSection').classList.add('d-none');
        document.getElementById('timerSection').classList.add('d-none');

        // Genera il contenuto finale come stringa di testo
        const finalContent = `
            <div class="container py-5 my-4 bg-dark rounded shadow text-center text-white">
                <img src="quiz.webp" class="img-fluid w-50 border rounded-4 shadow mb-4" alt="Quiz">
                <h1 class="mb-3 text-success">Hai completato il test!</h1>
                <p class="lead fs-2">Grazie per aver partecipato al test.</p>
            </div>
        `;

        // Sostituisce il contenuto principale con il nuovo contenuto generato
        document.getElementById('mainContent').innerHTML = finalContent;

        // Restituisce il testo HTML come stringa
        return finalContent;
    }

    // Salva risposte aperte
    document.getElementById('openQuestionsForm').addEventListener('input', (event) => {
        const { id, value } = event.target;
        userAnswers.open[id] = value;
    });

    // Salva risposte chiuse
    document.getElementById('closedQuestionsForm').addEventListener('change', (event) => {
        const { name, value } = event.target;
        userAnswers.closed[name] = value;
    });

    // Funzione per scaricare le risposte
    function downloadResults() {
        const results = `
    Risposte del Test:
        
    Domande Aperte:
    1. ${userAnswers.open.q1 || 'Non risposto'}
    2. ${userAnswers.open.q2 || 'Non risposto'}
    3. ${userAnswers.open.q3 || 'Non risposto'}
    4. ${userAnswers.open.q6 || 'Non risposto'}
    
    Domande Chiuse:
    4. ${userAnswers.closed.q4 || 'Non risposto'}
    5. ${userAnswers.closed.q5 || 'Non risposto'}
    6. ${userAnswers.closed.q7 || 'Non risposto'}
        `;
    
        const blob = new Blob([results], { type: 'text/plain' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'risposte_test.txt';
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
    }
    

    // Eventi
    document.getElementById('startButton').addEventListener('click', () => {
        document.getElementById('introSection').classList.add('d-none');
        document.getElementById('openQuestionsSection').classList.remove('d-none');
        document.getElementById('timerSection').classList.remove('d-none');
        timerInterval = setInterval(updateTimer, 1000);
    });

    document.getElementById('proceedButton').addEventListener('click', () => {
        document.getElementById('openQuestionsSection').classList.add('d-none');
        document.getElementById('closedQuestionsSection').classList.remove('d-none');
    });

    document.getElementById('closedQuestionsForm').addEventListener('submit', (event) => {
        event.preventDefault();
        completeTest();
    });

    // Event listener per il pulsante "Scarica Risultati"
    document.addEventListener('click', (event) => {
        if (event.target && event.target.id === 'downloadButton') {
            downloadResults();
        }
    });


});
