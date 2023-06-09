//création d'une liste availablePlayers qui contiendra les joueurs disponibles

// function highlight(theButton){
//     theButton.style.fontWeight = "bold";
//     theButton.style.fontSize = "110%";
//     var buttons = document.getElementsByClassName("btn");
//         for (var i = 0; i < buttons.length; i++) {
//             if (buttons[i] !== theButton) {
//                 buttons[i].disabled = true;
//                 buttons[i].style.opacity = 0.5;
//             }
//         }
// }


let userStatesList= [0,0,0,0];


//je veux que cette fonction ne fonctionne que sur index.html
if (window.location.pathname == "/index.html") {
let myInterval = setInterval((yee) => {
    
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
                buttons[i].style.opacity = 0.5;
                
            }
        }

        if (count == 4) {//si les 4 joueurs sont choisis, on arrête l'interval sur toutes les pages
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

    //on ouvre game_page.html dans une nouvelle fenêtre
    window.open("game_page.html", "_self");
    //arret de la fonction interval pour ne pas avoir de conflit
    //clearInterval(myInterval);
}



var leftButton = document.querySelector('.left');
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


var rightButton = document.querySelector('.right');
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
// Fonction pour mettre à jour la page
function update() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "update", true);
    xhttp.send();
}



leftButton.addEventListener('touchstart', leftButtonDown);
leftButton.addEventListener('touchend', leftButtonUp);
rightButton.addEventListener('touchstart', rightButtonDown);
rightButton.addEventListener('touchend', rightButtonUp);
