fetch('./socket.json')
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

        // Socket Intro
        document.getElementById('intro-title').innerText = data.socket.intro.title;
        document.getElementById('intro-description').innerText = data.socket.intro.description;

        // TCP Card
        document.getElementById('tcp-img').src = data.socket.tcpCard.img;
        document.getElementById('tcp-text').innerText = data.socket.tcpCard.text;

        // TCP Modal
        document.querySelector('#tcpModal').addEventListener('show.bs.modal', () => {
            document.getElementById('tcpModalImg').src = data.socket.tcpCard.modal.img;
            document.getElementById('tcpModalTitle').innerText = data.socket.tcpCard.modal.title;
            document.getElementById('tcpModalDescription').innerText = data.socket.tcpCard.modal.description;
        });

        // UDP Card
        document.getElementById('udp-img').src = data.socket.udpCard.img;
        document.getElementById('udp-text').innerText = data.socket.udpCard.text;

        // UDP Modal
        document.querySelector('#udpModal').addEventListener('show.bs.modal', () => {
            document.getElementById('udpModalImg').src = data.socket.udpCard.modal.img;
            document.getElementById('udpModalTitle').innerText = data.socket.udpCard.modal.title;
            document.getElementById('udpModalDescription').innerText = data.socket.udpCard.modal.description;
        });

        // Types of socket
        document.getElementById('types-title').innerText = data.socket.types.title;
        document.getElementById('types-description').innerText = data.socket.types.description;
        const typesCategories = document.getElementById('types-categories');
        data.socket.types.categories.forEach((category) => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>${category.name}:</strong> ${category.description}`;
            typesCategories.appendChild(li);
        });

        // Process of communication
        document.getElementById('process-title').innerText = data.socket.process.title;
        document.getElementById('process-description').innerText = data.socket.process.description;

        const rolesList = document.getElementById('process-steps');
        data.socket.process.steps.forEach((step) => {
            const li = document.createElement('li');
            li.innerText = step;
            rolesList.appendChild(li);
        });

        // Footer
        document.getElementById('footer-text').innerText = data.footer.text;
        document.getElementById('footer-small-text').innerHTML = data.footer.smallText;
    })
    .catch((error) => {
        console.error('Errore nel caricamento del file JSON:', error);
    });
