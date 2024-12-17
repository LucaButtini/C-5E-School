
fetch('./home.json')
    .then((res) => res.json())  
    .then((data) => {
        // Navbar
        const navbarLinks = document.querySelector('.navbar-nav');  
        data.navbar.links.forEach((link) => {
            const li = document.createElement('li');  
            li.className = 'nav-item';  
            li.innerHTML = `<a class="nav-link ${link.active ? 'active' : ''}" href="${link.href}">${link.text}</a>`;  
            navbarLinks.appendChild(li); 
        });

        // sezione principale
        document.querySelector('.container.mt-5').className = data.mainContent.containerClass;  
        document.querySelector('h1').innerHTML = `<span class="${data.mainContent.title.class}">${data.mainContent.title.strong ? `<strong>${data.mainContent.title.text}</strong>` : data.mainContent.title.text}</span>`;  
        document.querySelector('.lead').innerText = data.mainContent.description.text;  

        
        const mainContent = document.querySelector('.row.mt-4');  
        data.mainContent.sections.forEach((section) => {
            
            const row = document.createElement('div'); 
            row.className = section.type;  
            section.columns.forEach((col) => {
                
                const column = document.createElement('div');  
                column.className = col.class;  
                if (col.card) {
                    
                    const card = document.createElement('div');  
                    card.className = 'card h-100 bg-black text-white rounded-3';  
                    card.innerHTML = `
                        <img src="${col.card.image}" class="card-img-top" alt="${col.card.alt}">
                        <div class="card-body">
                            <p class="card-text">${col.card.text}</p>
                        </div>
                    `;  
                    column.appendChild(card); 
                } else if (col.content) {
                    // Se la colonna ha del contenuto
                    col.content.forEach((item) => {
                        const element = document.createElement(item.type);  
                        if (item.type === 'ul') {
                           
                            item.items.forEach((listItem) => {
                                const li = document.createElement('li');  
                                li.innerText = listItem;  
                                element.appendChild(li); 
                            });
                        } else {
                            
                            element.innerHTML = item.strong ? `<strong>${item.text}</strong>` : item.text;  
                        }
                        column.appendChild(element);  
                    });
                }
                row.appendChild(column);  
            });
            mainContent.appendChild(row);  
        });

        document.getElementById('footer-text').innerText = data.footer.text;
        document.getElementById('footer-small-text').innerHTML = data.footer.smallText;

        
        data.scripts.forEach((script) => {
            const scriptTag = document.createElement('script');  
            scriptTag.src = script;  
            scriptTag.type = 'text/javascript';  
            document.body.appendChild(scriptTag);  
        });
    })
    .catch((error) => {
        console.error('Errore nel caricamento del file JSON:', error); 
    });
