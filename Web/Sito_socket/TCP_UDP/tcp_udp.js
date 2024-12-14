fetch('./tcp_udp.json')
    .then((res) => res.json())
    .then((data) => {
        //navbar
        const navbarLinks = document.getElementById('navbar-links');
        data.navbarLinks.forEach((link) => {
            const li = document.createElement('li');
            li.className = 'nav-item';
            li.innerHTML = `<a class="nav-link ${link.active ? 'active' : ''}" href="${link.href}">${link.text}</a>`;
            navbarLinks.appendChild(li);
        });

        //titolo descrizione
        document.getElementById('page-title').innerText = data.pageTitle;
        document.getElementById('page-description').innerText = data.pageDescription;

        //tcp
        document.getElementById('tcp-img').src = data.tcp.img;
        document.getElementById('tcp-card-text').innerText = data.tcp.cardText;
        document.getElementById('tcp-title').innerText = data.tcp.title;
        document.getElementById('tcp-description').innerText = data.tcp.description;

        const tcpFeatures = document.getElementById('tcp-features');
        data.tcp.features.forEach((feature) => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>${feature.strong}:</strong> ${feature.text}`;
            tcpFeatures.appendChild(li);
        });

        //udp
        document.getElementById('udp-img').src = data.udp.img;
        document.getElementById('udp-card-text').innerText = data.udp.cardText;
        document.getElementById('udp-title').innerText = data.udp.title;
        document.getElementById('udp-description').innerText = data.udp.description;

        const udpFeatures = document.getElementById('udp-features');
        data.udp.features.forEach((feature) => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>${feature.strong}:</strong> ${feature.text}`;
            udpFeatures.appendChild(li);
        });

        // Footer 
        document.getElementById('footer-text').innerText = data.footer.text;
        document.getElementById('footer-small-text').innerHTML = data.footer.smallText;

        // Modal Event Listeners
        document.querySelector('#tcpModal').addEventListener('show.bs.modal', () => {
            document.getElementById('tcp-modal-img').src = data.tcp.img;
            document.getElementById('tcp-modal-text').innerHTML = data.tcp.modal.text;

            // steps tcp
            const tcpSteps = document.getElementById('tcp-steps');
            tcpSteps.innerHTML = ''; 
            data.tcp.modal.steps.forEach((step) => {
                const li = document.createElement('li');
                li.innerHTML = `<strong>${step.step}:</strong> ${step.description}`;
                tcpSteps.appendChild(li);
            });
        });

        document.querySelector('#udpModal').addEventListener('show.bs.modal', () => {
            document.getElementById('udp-modal-img').src = data.udp.img;
            document.getElementById('udp-modal-text').innerHTML = data.udp.modal.text;
        });
    });