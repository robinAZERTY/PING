var leftButton = document.querySelector('.left');
function leftButtonDown() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "leftDown", true);
    xhttp.send();

}
function leftButtonUp() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "leftUp", true);
    xhttp.send();
}



var leftButton = document.querySelector('.right');
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
