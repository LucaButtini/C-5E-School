document.addEventListener('DOMContentLoaded', () => {
    // Timer
    let totalSeconds = 600; // 10 minuti (600 secondi)

    function updateTimer() {
        const minutes = Math.floor(totalSeconds / 60);
        const seconds = totalSeconds % 60;
        document.getElementById('time').textContent = `${minutes}:${seconds < 10 ? '0' : ''}${seconds}`;
        totalSeconds--;

        if (totalSeconds < 0) {
            clearInterval(timerInterval);
            alert('Tempo scaduto! Il test verrà salvato automaticamente.');
            saveTest();
        }
    }
    const timerInterval = setInterval(updateTimer, 1000);

    // Gestione del submit
    document.getElementById('closedQuestionsForm').addEventListener('submit', (event) => {
        event.preventDefault(); // Evita il refresh della pagina
        saveTest();
    });

    // Funzione per salvare il test in un file
    function saveTest() {
        const openFormData = new FormData(document.getElementById('openQuestionsForm'));
        const closedFormData = new FormData(document.getElementById('closedQuestionsForm'));
        const results = [];

        // Raccogli le risposte
        openFormData.forEach((value, key) => {
            results.push(`${key}: ${value}`);
        });
        closedFormData.forEach((value, key) => {
            results.push(`${key}: ${value}`);
        });

        // Crea un file di testo
        const blob = new Blob([results.join('\n')], { type: 'text/plain' });
        const url = URL.createObjectURL(blob);

        // Creazione del link per scaricare il file
        const a = document.createElement('a');
        a.href = url;
        a.download = `risultati_test_${new Date().toISOString().slice(0, 19).replace(/:/g, '-')}.txt`;
        a.click();

        // Cleanup
        URL.revokeObjectURL(url);
        alert('Test salvato correttamente!');
    }

    // Mostra la sezione delle domande aperte
    document.getElementById('startButton').addEventListener('click', () => {
        document.getElementById('introSection').classList.add('d-none'); // Nasconde l'introduzione
        document.getElementById('openQuestionsSection').classList.remove('d-none'); // Mostra domande aperte
    });

    // Mostra la sezione delle domande chiuse
    document.getElementById('proceedButton').addEventListener('click', () => {
        document.getElementById('openQuestionsSection').classList.add('d-none'); // Nasconde domande aperte
        document.getElementById('closedQuestionsSection').classList.remove('d-none'); // Mostra domande chiuse
    });
});
