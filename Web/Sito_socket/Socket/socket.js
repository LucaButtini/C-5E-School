fetch('./socket.json')
    .then((res) => res.json())
    .then((data) => {
        // Navbar Brand
        document.querySelector('.navbar-brand').innerText = data.navbar.brand;

        // Navbar Links
        const navbarLinks = document.getElementById('navbar-links');
        data.navbar.links.forEach((link) => {
            const li = document.createElement('li');
            li.className = 'nav-item';
            li.innerHTML = `<a class="nav-link ${link.active ? 'active' : ''}" href="${link.href}">${link.text}</a>`;
            navbarLinks.appendChild(li);
        });

        // Page Title and Description
        document.querySelector('.display-3').innerText = data.pageTitle;
        document.querySelector('.lead').innerText = data.pageDescription;

        // Socket Intro
        document.querySelector('h2').innerText = data.socketIntro.title;
        document.querySelector('h2 + p').innerText = data.socketIntro.description;

        // TCP Card
        document.querySelector('#tcp-img').src = data.tcpCard.img;
        document.querySelector('#tcp-img').alt = data.tcpCard.text;
        document.querySelector('#tcp-img + .card-body .card-text').innerHTML = data.tcpCard.text;

        // Add Event Listener for TCP Modal
        document.querySelector('#socketModal1').addEventListener('show.bs.modal', () => {
            document.getElementById('tcpModalImg').src = data.tcpCard.modal.img;
            document.getElementById('tcpModalLabel1').innerText = data.tcpCard.modal.title;
            document.getElementById('tcpModalDescription1').innerText = data.tcpCard.modal.description;
        });

        // UDP Card
        document.querySelector('#udp-img').src = data.udpCard.img;
        document.querySelector('#udp-img').alt = data.udpCard.text;
        document.querySelector('#udp-img + .card-body .card-text').innerHTML = data.udpCard.text;

        // Add Event Listener for UDP Modal
        document.querySelector('#socketModal2').addEventListener('show.bs.modal', () => {
            document.getElementById('udpModalImg').src = data.udpCard.modal.img;
            document.getElementById('udpModalLabel2').innerText = data.udpCard.modal.title;
            document.getElementById('udpModalDescription2').innerText = data.udpCard.modal.description;
        });

        // Types of Socket
        document.querySelector('.col-md-6 h2').innerText = data.types.title;
        document.querySelector('.col-md-6 p').innerText = data.types.description;
        const typesList = document.querySelector('.col-md-6 ul');
        data.types.categories.forEach((category) => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>${category.name}:</strong> ${category.description}`;
            typesList.appendChild(li);
        });

        // Process of Communication
        document.querySelector('.col-md-12 h2').innerText = data.process.title;
        document.querySelector('.col-md-12 p').innerText = data.process.description;

        const processSteps = document.querySelector('.col-md-12 ul');
        processSteps.innerHTML = ''; // Clear existing list
        data.process.steps.forEach((step) => {
            const li = document.createElement('li');
            li.innerText = step;
            processSteps.appendChild(li);
        });

        // Footer
        document.getElementById('footer-text').innerText = data.footer.text;
        document.getElementById('footer-small-text').innerHTML = data.footer.smallText;
    })
    .catch((error) => {
        console.error('Errore nel caricamento del file JSON:', error);
    });
