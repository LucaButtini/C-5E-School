// Carica il file JSON contenente i dati per la pagina
fetch('./home.json')
    .then((res) => res.json())  // Converte la risposta in formato JSON
    .then((data) => {
        // Navbar: Popola i link della navbar
        const navbarLinks = document.querySelector('.navbar-nav');  // Seleziona il container della navbar
        data.navbar.links.forEach((link) => {
            const li = document.createElement('li');  // Crea un nuovo elemento <li> per ogni link
            li.className = 'nav-item';  // Aggiunge la classe per lo stile della navbar
            li.innerHTML = `<a class="nav-link ${link.active ? 'active' : ''}" href="${link.href}">${link.text}</a>`;  // Aggiunge il link con la classe 'active' se il link è attivo
            navbarLinks.appendChild(li);  // Aggiunge il <li> appena creato nella navbar
        });

        // Sezione principale: Imposta il titolo e la descrizione principale
        document.querySelector('.container.mt-5').className = data.mainContent.containerClass;  // Imposta la classe della container principale
        document.querySelector('h1').innerHTML = `<span class="${data.mainContent.title.class}">${data.mainContent.title.strong ? `<strong>${data.mainContent.title.text}</strong>` : data.mainContent.title.text}</span>`;  // Imposta il titolo principale
        document.querySelector('.lead').innerText = data.mainContent.description.text;  // Imposta la descrizione principale

        // Sezioni: Popola le varie sezioni della pagina
        const mainContent = document.querySelector('.row.mt-4');  // Seleziona la riga principale per le sezioni
        data.mainContent.sections.forEach((section) => {
            // Sezione tipo "row"
            const row = document.createElement('div');  // Crea una nuova <div> per la riga
            row.className = section.type;  // Aggiunge la classe per la riga
            section.columns.forEach((col) => {
                // Colonne all'interno della riga
                const column = document.createElement('div');  // Crea una nuova <div> per la colonna
                column.className = col.class;  // Aggiunge la classe per la colonna
                if (col.card) {
                    // Se la colonna ha una card, la aggiungi
                    const card = document.createElement('div');  // Crea una nuova card
                    card.className = 'card h-100 bg-black text-white rounded-3';  // Imposta lo stile della card
                    card.innerHTML = `
                        <img src="${col.card.image}" class="card-img-top" alt="${col.card.alt}">
                        <div class="card-body">
                            <p class="card-text">${col.card.text}</p>
                        </div>
                    `;  // Aggiungi l'immagine e il testo alla card
                    column.appendChild(card);  // Aggiungi la card alla colonna
                } else if (col.content) {
                    // Se la colonna ha del contenuto
                    col.content.forEach((item) => {
                        const element = document.createElement(item.type);  // Crea un nuovo elemento (h2, p, ul, etc.)
                        if (item.type === 'ul') {
                            // Se è una lista, aggiungi gli elementi della lista
                            item.items.forEach((listItem) => {
                                const li = document.createElement('li');  // Crea un <li> per ogni elemento della lista
                                li.innerText = listItem;  // Aggiungi il testo all'elemento della lista
                                element.appendChild(li);  // Aggiungi il <li> alla lista
                            });
                        } else {
                            // Per gli altri tipi di elementi, imposta solo il testo
                            element.innerHTML = item.strong ? `<strong>${item.text}</strong>` : item.text;  // Se c'è la proprietà 'strong', aggiungi il <strong>
                        }
                        column.appendChild(element);  // Aggiungi l'elemento alla colonna
                    });
                }
                row.appendChild(column);  // Aggiungi la colonna alla riga
            });
            mainContent.appendChild(row);  // Aggiungi la riga alla sezione principale
        });

        // Footer: Popola il contenuto del footer
        const footer = document.getElementById('foot-home');  // Seleziona il footer
        data.footer.content.forEach((item) => {
            const element = document.createElement(item.type);  // Crea un nuovo elemento (p, small, etc.)
            element.className = item.class;  // Aggiungi la classe
            element.innerHTML = item.text;  // Imposta il testo dell'elemento
            footer.appendChild(element);  // Aggiungi l'elemento al footer
        });

        // Scripts: Aggiungi i file JavaScript esterni
        data.scripts.forEach((script) => {
            const scriptTag = document.createElement('script');  // Crea un nuovo tag <script>
            scriptTag.src = script;  // Imposta la fonte del file JavaScript
            scriptTag.type = 'text/javascript';  // Imposta il tipo del file
            document.body.appendChild(scriptTag);  // Aggiungi il tag <script> al corpo della pagina
        });
    })
    .catch((error) => {
        console.error('Errore nel caricamento del file JSON:', error);  // Gestione degli errori in caso di problemi nel caricamento del file JSON
    });
