fetch('./glossario.json')
    .then(res => res.json())
    .then(data => {

        document.title = data.title; //titolo pagina


        document.querySelector("link[rel='icon']").href = data.meta.icon; //icona

        //navbar
        const navbar = document.querySelector('.navbar-nav');
        data.navbar.links.forEach(link => {
            const li = document.createElement('li');
            li.classList.add('nav-item');
            const a = document.createElement('a');
            a.classList.add('nav-link');
            if (link.active)
                a.classList.add('active');
            a.href = link.href;
            a.textContent = link.text;
            li.appendChild(a);
            navbar.appendChild(li);
        });

        //contenuto del glossario
        const contentContainer = document.querySelector('.container.mt-5');
        const introduction = data.content.introduction;

        //introduzione 
        const introDiv = document.createElement('div');
        introDiv.classList.add('text-center');
        const introTitle = document.createElement('h1');
        introTitle.classList.add('display-3', 'mb-3', 'text-primary', 'ombra');
        introTitle.textContent = introduction.title;
        const introLead = document.createElement('p');
        introLead.classList.add('lead');
        introLead.textContent = introduction.lead;
        introDiv.appendChild(introTitle);
        introDiv.appendChild(introLead);
        contentContainer.appendChild(introDiv);

        //list group glossario
        const ul = document.createElement('ul');
        ul.classList.add('list-group', 'text-center');

       //aggiungo ogni termine
        data.content.sections.forEach(section => {
            section.items.forEach(item => {
                const li = document.createElement('li');
                li.classList.add('list-group-item', 'text-light', 'bg-dark', 'p-5');

                const strong = document.createElement('strong');
                strong.textContent = `${item.title}: `;
                li.appendChild(strong);

                const description = document.createElement('span');
                description.innerHTML = item.description;
                li.appendChild(description);

                ul.appendChild(li);
            });
        });

        contentContainer.appendChild(ul);

        //footer
        const footer = document.querySelector('footer');
        footer.querySelector('.display-6').textContent = data.footer.text;
        footer.querySelector('small').innerHTML = data.footer.smallText;
    })
    .catch(error => {
        console.error("Error loading the glossary:", error);
    });
