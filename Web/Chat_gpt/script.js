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
        // Definiamo le domande
        const openQuestions = [
            "1. Descrivi brevemente il funzionamento di un protocollo di rete.",
            "2. Qual è la differenza tra HTTP e HTTPS?",
            "3. Spiega il concetto di indirizzo IP.",
            "4. Cosa sono le ACL?",
            "5. Descrivi come funziona una VPN.",
            "6. Che cos'è una socket?"
        ];

        const closedQuestions = [
            "1. Quale tra i seguenti è un protocollo di trasporto?",
            "2. Quale porta viene tipicamente usata per HTTP?",
            "3. Quale dei seguenti è un protocollo di sicurezza?",
            "4. Qual è il protocollo più usato per l'invio di email?",
            "5. Quale porta usa tipicamente SSH?",
            "6. Cos'è un DNS?"
        ];

        // Risposte corrette
        const correctAnswersOpen = [
            "Un protocollo di rete è un insieme di regole che definiscono la comunicazione tra dispositivi.",
            "HTTP è non sicuro, mentre HTTPS utilizza una connessione sicura tramite SSL/TLS.",
            "Un indirizzo IP è un identificatore numerico che un dispositivo utilizza per comunicare in una rete.",
            "Le ACL (Access Control List) definiscono chi può accedere a una risorsa e cosa può fare.",
            "Una VPN crea una connessione sicura tra il tuo dispositivo e un altro tramite internet.",
            "Una socket è un endpoint per la comunicazione tra due dispositivi attraverso una rete."
        ];

        const correctAnswersClosed = [
            "TCP/UDP",
            "80",
            "SSL/TLS",
            "SMTP",
            "22",
            "Un sistema che traduce i nomi di dominio in indirizzi IP."
        ];

        // Componiamo i risultati
        let results = "Risposte del Test:\n\n";

        // Domande Aperte e Risposte
        results += "Domande Aperte:\n";
        for (let i = 0; i < openQuestions.length; i++) {
            const question = openQuestions[i];
            const answer = userAnswers.open[`q${i + 1}`] || 'Non risposto';
            results += `${question}\n${answer}\n\n`;
        }

        // Domande Chiuse e Risposte
        results += "Domande Chiuse:\n";
        for (let i = 0; i < closedQuestions.length; i++) {
            const question = closedQuestions[i];
            const answer = userAnswers.closed[`q${i + 7}`] || 'Non risposto'; // Le domande chiuse partono da q7
            results += `${question}\n${answer}\n\n`;
        }

        // Separatore
        results += "----------------------\n\n";

        // Risposte Corrette
        results += "Risposte Corrette:\n\n";

        // Risposte Corrette per le Domande Aperte
        results += "Domande Aperte:\n";
        for (let i = 0; i < correctAnswersOpen.length; i++) {
            results += `${openQuestions[i]}\n${correctAnswersOpen[i]}\n\n`;
        }

        // Risposte Corrette per le Domande Chiuse
        results += "Domande Chiuse:\n";
        for (let i = 0; i < correctAnswersClosed.length; i++) {
            results += `${closedQuestions[i]}\n${correctAnswersClosed[i]}\n\n`;
        }

        // Creazione del Blob e download
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

    document.addEventListener('click', (event) => {
        if (event.target && event.target.id === 'restartButton') {
            // Reimposta le variabili e il contenuto
            totalSeconds = 600;  // 10 minuti
            userAnswers.open = {};
            userAnswers.closed = {};

            // Ripristina il timer e le domande
            document.getElementById('mainContent').innerHTML = document.getElementById('introSection').outerHTML;

            // Nascondi e mostra le sezioni
            document.getElementById('openQuestionsSection').classList.add('d-none');
            document.getElementById('closedQuestionsSection').classList.add('d-none');
            document.getElementById('timerSection').classList.add('d-none');
            document.getElementById('introSection').classList.remove('d-none');

            // Resetta il timer
            document.getElementById('time').textContent = '10:00';
        }
    });

    // Event listener per il pulsante "Scarica Risultati"
    document.addEventListener('click', (event) => {
        if (event.target && event.target.id === 'downloadButton') {
            downloadResults();
        }
    });


});