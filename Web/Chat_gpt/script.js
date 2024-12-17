document.addEventListener('DOMContentLoaded', () => {
    let totalSeconds = 600; // 10 minuti
    let timerInterval;
    let timeTaken; // Per salvare il tempo finale

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
        timeTaken = 600 - totalSeconds - 1; // Tempo impiegato in secondi
        const finalMinutes = Math.floor(timeTaken / 60);
        const finalSeconds = timeTaken % 60;

        // Nascondi tutte le sezioni delle domande e il timer
        document.getElementById('openQuestionsSection').classList.add('d-none');
        document.getElementById('closedQuestionsSection').classList.add('d-none');
        document.getElementById('timerSection').classList.add('d-none');

        // Crea il messaggio finale
        const finalMessage = `
            <div class="container py-5 my-4 bg-white rounded shadow text-center">
                <h1 class="mb-3 text-success">Hai completato il test!</h1>
                <p class="fs-4 text-secondary">Tempo impiegato: <strong>${finalMinutes} minuti e ${finalSeconds} secondi</strong></p>
            </div>
        `;

        // Inserisce il messaggio al posto delle sezioni nascoste
        const mainContent = document.getElementById('mainContent');
        mainContent.innerHTML = finalMessage;
    }

    // Raccolta risposte
    function collectResults() {
        const results = [];

        // Raccolta domande aperte
        const openQuestionsSection = document.getElementById('openQuestionsSection');
        if (openQuestionsSection) {
            const openQuestions = openQuestionsSection.querySelectorAll('textarea');
            openQuestions.forEach((textarea, index) => {
                const answer = textarea.value.trim();
                results.push(`Domanda ${index + 1}: ${answer || "Non risposto"}`);
            });
        }

        // Raccolta domande chiuse
        const closedQuestionsSection = document.getElementById('closedQuestionsSection');
        if (closedQuestionsSection) {
            const closedQuestions = closedQuestionsSection.querySelectorAll('input[type="radio"]');
            const groupedQuestions = {};

            // Raggruppa per "name" le risposte selezionate
            closedQuestions.forEach((input) => {
                if (input.checked) {
                    groupedQuestions[input.name] = input.value;
                } else if (!groupedQuestions[input.name]) {
                    groupedQuestions[input.name] = "Non risposto";
                }
            });

            // Salva le risposte raccolte
            Object.keys(groupedQuestions).forEach((name, index) => {
                results.push(`Domanda ${index + 4}: ${groupedQuestions[name]}`);
            });
        }

        return results;
    }

    // Salva i risultati su file
    function saveResults() {
        const results = collectResults();
        console.log("Risultati raccolti:", results); // Debug in console

        if (results.length === 0) {
            alert("Non ci sono risposte da salvare!");
            return;
        }

        // Genera il file .txt
        const blob = new Blob([results.join('\n')], { type: 'text/plain' });
        const url = URL.createObjectURL(blob);

        // Crea e simula il click sul link per scaricare
        const a = document.createElement('a');
        a.href = url;
        a.download = `test_results_${new Date().toISOString().replace(/[:]/g, '-')}.txt`;
        a.click();

        // Rilascia l'URL per evitare memory leak
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

    document.getElementById('downloadButton').addEventListener('click', saveResults);
});
