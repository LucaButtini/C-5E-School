
fetch('./iso_osi.json')
    .then((res) => res.json()) 
    .then((data) => {
       
        const navbarLinks = document.getElementById('navbar-links'); 
        data.navbar.links.forEach((link) => {
            const li = document.createElement('li');
            li.className = 'nav-item'; 
            li.innerHTML = `<a class="nav-link ${link.active ? 'active' : ''}" href="${link.href}">${link.text}</a>`; 
            navbarLinks.appendChild(li); 
        });

        // Titolo e Descrizione
        document.getElementById('page-title').innerText = data.pageTitle; 
        document.getElementById('page-description').innerText = data.pageDescription; 

        // OSI Descrizione
        document.getElementById('osi-img').src = data.osi.img; 
        document.getElementById('osi-card-text').innerText = data.osi.cardText; 
        document.getElementById('osi-description').innerText = data.osi.description; 

        // carosello
        const osiLevels = document.getElementById('osi-levels'); 
        data.osi.levels.forEach((level, index) => {
            const div = document.createElement('div'); 
            div.className = `carousel-item ${index === 0 ? 'active' : ''}`; 
            div.innerHTML = `
                <h4>${level.name}</h4> <!-- Nome del livello -->
                <p>${level.description}</p> <!-- Descrizione del livello -->
            `; 
            osiLevels.appendChild(div); 
        });

        // Footer
        document.getElementById('footer-text').innerText = data.footer.text; 
        document.getElementById('footer-small-text').innerHTML = data.footer.smallText; 

        // Modal
        document.querySelector('#osiModal').addEventListener('show.bs.modal', () => {
            document.getElementById('osi-modal-img').src = data.osi.modal.img; 
            document.getElementById('osi-modal-description').innerText = data.osi.modal.description; 
            document.getElementById('osiModalLabel').innerText = data.osi.modal.title; 
        });
    })
    .catch((error) => {
        console.error('Errore nel caricamento del file JSON:', error); 
    });
