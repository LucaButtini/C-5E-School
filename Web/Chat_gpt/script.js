document.addEventListener('DOMContentLoaded', () => {
    let totalSeconds = 600; // 10 minuti
    let timerInterval;

    const userAnswers = {
        open: {},
        closed: {}
    };

    // Timer
    const startTimer = () => {
        timerInterval = setInterval(() => {
            totalSeconds--;
            const minutes = Math.floor(totalSeconds / 60);
            const seconds = totalSeconds % 60;
            document.getElementById('time').textContent = `${minutes}:${seconds.toString().padStart(2, '0')}`;

            if (totalSeconds === 0) {
                clearInterval(timerInterval);
                alert('Tempo scaduto! Il test verrà inviato automaticamente.');
                submitTest();
            }
        }, 1000);
    };

    // Sezione iniziale
    document.getElementById('startButton').addEventListener('click', () => {
        document.getElementById('introSection').classList.add('d-none');
        document.getElementById('openQuestionsSection').classList.remove('d-none');
        document.getElementById('timerSection').classList.remove('d-none');
        startTimer();
    });

    // Procedi alle domande chiuse
    document.getElementById('proceedButton').addEventListener('click', () => {
        const openQuestionsForm = document.getElementById('openQuestionsForm');
        const formData = new FormData(openQuestionsForm);

        formData.forEach((value, key) => {
            userAnswers.open[key] = value;
        });

        document.getElementById('openQuestionsSection').classList.add('d-none');
        document.getElementById('closedQuestionsSection').classList.remove('d-none');
    });

    // Completa il test
    document.getElementById('closedQuestionsForm').addEventListener('submit', (event) => {
        event.preventDefault();

        const closedQuestionsForm = document.getElementById('closedQuestionsForm');
        const formData = new FormData(closedQuestionsForm);

        formData.forEach((value, key) => {
            userAnswers.closed[key] = value;
        });

        submitTest();
    });

    // Scarica i risultati
    document.getElementById('downloadButton').addEventListener('click', () => {
        const blob = new Blob([JSON.stringify(userAnswers, null, 2)], { type: 'application/json' });
        const a = document.createElement('a');
        a.href = URL.createObjectURL(blob);
        a.download = 'test_results.json';
        a.click();
    });

    // Invia il test
    const submitTest = () => {
        clearInterval(timerInterval);
        document.getElementById('timerSection').classList.add('d-none');
        document.getElementById('closedQuestionsSection').classList.add('d-none');
        document.getElementById('introSection').classList.remove('d-none');

        console.log('Risultati del test:', userAnswers);
        alert('Test completato con successo!');
    };
});
