fetch('./home.json')
    .then((res) => res.json())
    .then((data) => {
        // Navbar Brand
        document.getElementById('navbar-brand').innerText = data.navbar.brand;

        // Navbar Links
        const navbarLinks = document.getElementById('navbar-links');
        data.navbar.links.forEach((link) => {
            const li = document.createElement('li');
            li.className = 'nav-item';
            li.innerHTML = `<a class="nav-link ${link.active ? 'active' : ''}" href="${link.href}">${link.text}</a>`;
            navbarLinks.appendChild(li);
        });

        // Page Title and Description
        document.getElementById('page-title').innerText = data.pageTitle;
        document.getElementById('page-description').innerText = data.pageDescription;

        // Socket Card
        document.getElementById('socket-img').src = data.socketCard.img;
        document.getElementById('socket-img').alt = data.socketCard.text;
        document.getElementById('socket-text').innerText = data.socketCard.text;

        // Socket Modal
        document.querySelector('.card').addEventListener('click', () => {
            document.getElementById('tcpModalImg').src = data.socketCard.modal.img;
            document.getElementById('tcpModalLabel').innerText = data.socketCard.modal.title;
            document.getElementById('tcpModalDescription').innerText = data.socketCard.modal.description;
        });

        // Socket Intro
        document.getElementById('socket-title').innerText = data.socketIntro.title;
        document.getElementById('socket-description').innerText = data.socketIntro.description;

        // Site Features
        const siteFeatures = document.getElementById('site-features');
        data.siteFeatures.forEach((feature) => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>${feature.title}:</strong> ${feature.description}`;
            siteFeatures.appendChild(li);
        });

        // Footer
        document.getElementById('footer-text').innerText = data.footer.text;
        document.getElementById('footer-small-text').innerHTML = data.footer.smallText;
    })
    .catch((error) => {
        console.error('Errore nel caricamento del file JSON:', error);
    });
