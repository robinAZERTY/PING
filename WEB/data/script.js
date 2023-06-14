let userStatesList= [0,0,0,0];



if (window.location.pathname == "/index.html") {//si l'on est sur la page d'accueil
let myInterval = setInterval((yee) => {//on fait une requête au serveur toutes les 500ms pour récupérer la liste des joueurs choisis
    
    fetch("choosen-players").then(async (response) => {
        
        const states = await response.text()
        let userStatesList = []

        for (var i = 0; i < states.length; i++) {
            userStatesList.push(parseInt(states[i]));
        }

        console.log(states);
        console.log(userStatesList);
        
        let buttons = document.getElementsByClassName("btn");
        let count = 0;
        for (let i = 0; i < buttons.length; i++) {
            if (userStatesList[i] == 1) {
                count++;
                buttons[i].disabled = true;
                buttons[i].style.opacity = 0.3;
                
            }
        }

        if (count == 4) {//si les 4 joueurs sont choisis, on arrête l'interval 
            clearInterval(myInterval);            
            console.log("clearInteral")
            
        }

    })
}, 500);}


function bp(theButton, id) {
    
    // Stocker uniqueID dans les cookies
    localStorage.setItem('uniqueId', id);
    console.log(localStorage.getItem('uniqueId'));
    
    //on fait une requête au serveur pour lui mettre à jour la liste des joueurs disponibles
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "updateAvailablePlayers/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
    
}

function allAreReady(){
    //on attent la requete du serveur pour savoir si tous les joueurs sont prêts
    let myInterval = setInterval((yee) => {
        fetch("all-choosen").then(async (response) => {
            const states = await response.text()
            console.log(states);
            let userStatesList = []

            for (var i = 0; i < states.length; i++) {
                userStatesList.push(parseInt(states[i]));
            }
            console.log(userStatesList);

            //si la première valeur de la liste est égale à l'id, alors on ouvre start.html
            if (userStatesList[0] == localStorage.getItem('uniqueId')) {
                window.location.href = "start.html";
                clearInterval(myInterval);
            } 
            //dès que la conditions précédente est remplie, on arrête l'interval
            if (userStatesList[0] == 1) {
                clearInterval(myInterval);
            }
            
        })
    }, 500);
}

function startButton(){//quand on appuie sur le bouton start
    //on déclare une variable bool nommée "start" 
    let start = 1;
    //on fait une requête au serveur pour envoyer la valeur de "start"
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "start/?start=" + start, true);
    xhttp.send();

    
} 





let myInterval = setInterval((yee) => {
    fetch("gameStarted").then(async (response) => {
        const states = await response.text()
        console.log(states);
        //si on est sur la page start.html ou sur waiting.html, on ouvre game_page.html
        if ((window.location.pathname == "/start.html" || window.location.pathname == "/waiting_page.html")&& states == 1) {
            window.location.href = "game_page.html";
            clearInterval(myInterval);

        }
        //si on est sur la page game_page.html on arrete l'interval
        if (window.location.pathname == "/game_page.html") {
            clearInterval(myInterval);
        }

    })
}, 500);



    
    
    


            
       





function leftButtonDown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "leftDown/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
    console.log(localStorage.getItem('uniqueId'))

}
function leftButtonUp() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "leftUp/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
    console.log("leftUp");
}



function rightButtonDown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "rightDown/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
}
function rightButtonUp() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "rightUp/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
}



function pushButtonDown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "pushDown/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
}
function pushButtonUp() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "pushUp/?uniqueID=" + localStorage.getItem('uniqueId'), true);
    xhttp.send();
}




