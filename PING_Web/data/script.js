var availablePlayers = [1,2,3,4]
function bp1(theButton){
    
    //stocker uniqueID dans les cookies
    localStorage.setItem('uniqueId', 1);
    console.log(localStorage.getItem('uniqueId'))
    //supprimer uniqueID de la liste des joueurs disponibles
    availablePlayers.splice(availablePlayers.indexOf(1), 1);
    console.log(availablePlayers)
    //mettre en évidence le bouton du joueur sélectionné (taille de 10% plus grande et gras)
    theButton.style.fontWeight = "bold";
    theButton.style.fontSize = "110%";
       
    //modifier le css des autres boutons de la classe choix-joueurspour les rendre moins visibles (opacité à 0.5)
    var otherButtons = document.querySelectorAll('.');
    for (var i = 0; i < otherButtons.length; i++) {
        if (otherButtons[i] != theButton) {
            otherButtons[i].style.opacity = "0.5";
            otherButtons[i].disabled = true;
        }
    }
    
    

    
    
    
}
function bp2(){
    localStorage.setItem('uniqueId', 2);
    console.log(localStorage.getItem('uniqueId'))
}
function bp3(){
    localStorage.setItem('uniqueId', 3);
    console.log(localStorage.getItem('uniqueId'))  
}
function bp4(){
    localStorage.setItem('uniqueId', 4);
    console.log(localStorage.getItem('uniqueId'))  
}



var leftButton = document.querySelector('.left'); 
function leftButtonDown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "leftDown/?uniqueID="+localStorage.getItem('uniqueId'), true);
    xhttp.send();
    console.log(localStorage.getItem('uniqueId'))

}
function leftButtonUp() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "leftUp", true);
    xhttp.send();
}


var rightButton = document.querySelector('.right');
function rightButtonDown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "rightDown", true);
    xhttp.send();
}
function rightButtonUp() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "rightUp", true);
    xhttp.send();
}



function pushButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "push", true);
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
