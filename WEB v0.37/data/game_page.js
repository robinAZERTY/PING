const PLAYER_ACTION = {
    LEFT: "left",
    RIGHT: "right",
    STOP: "stop",
    PUNCH: "punch",
    STOP_PUNCH: "stop-punch",
    RESUME: "resume"
}

function getLivesRequest() {
    
    fetch("/getLives?playerId=" + localStorage.getItem("playerId").toString()).then(function (response) {
        return response.text();
    }).then(function (text) {
        if (DEBUG) console.log("getLives: " + text);
        refreshLivesDisplay(text);
    })

}

function refreshLivesDisplay(lives) {
    //get the lives display element
    let lives_display = document.getElementById("vies");
    let vie_img = document.createElement("img");
    vie_img.setAttribute("class", "coeur");
    vie_img.setAttribute("src", "/coeur.png");
    //on lui injecte le lives vies
    lives_display.innerHTML = "";
    for (let i = 0; i < lives; i++) {
        lives_display.appendChild(vie_img.cloneNode(true));
    }
}

function leftButtonDown()
{
    //on récupère le joueur
    const playerId = localStorage.getItem("playerId");

    //on construit le contenu de la requête
    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.LEFT,
    };
    sendDatas(data);
}

function rightButtonDown()
{
    //on récupère le joueur
    const playerId = localStorage.getItem("playerId").toString();

    //on construit le contenu de la requête
    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.RIGHT,
    };
    sendDatas(data);
}

function leftButtonUp()
{
    //on récupère le joueur
    const playerId = localStorage.getItem("playerId").toString();

    //on construit le contenu de la requête
    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.STOP,
    };
    sendDatas(data);
}

function rightButtonUp()
{
    //on récupère le joueur
    const playerId = localStorage.getItem("playerId").toString();

    //on construit le contenu de la requête
    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.STOP,
    };
    sendDatas(data);
}

let intervalId = 0;

function punchButtonDown()
{

    // // Répétition de la vibration tant que le bouton est maintenu enfoncé
    // intervalId = setInterval(function () {
    //     navigator.vibrate(100);
    // }, 100);
    //on récupère le joueur
    const playerId = localStorage.getItem("playerId").toString();
    
    //on construit le contenu de la requête
    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.PUNCH
    };
    sendDatas(data);
}

function punchButtonUp()
{   

    //on récupère le joueur
    const playerId = localStorage.getItem("playerId").toString();

    //on construit le contenu de la requête
    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.STOP_PUNCH
    };
    sendDatas(data);
}

function sendDatas(data)
{
    if (data.length == 0) return;

    //on construit la requête
    //if (DEBUG) console.log("sendDatas: " + data);

    let dataToSend = "/playerAction?";
    for (let key in data) {
        dataToSend += key + "=" + data[key];
        dataToSend += "&";
    }
    dataToSend = dataToSend.slice(0, -1);

    if (DEBUG) console.log("sendDatas: " + dataToSend);

    fetch(dataToSend);
}


function resume()
{
    //on envoit une requête pour dire qu'on reprend (avec l'id en paramètre)
    //on remet à jour l'affichage des boutons
    const playerId = localStorage.getItem("playerId").toString();

    const data = {
        "playerId": playerId,
        "action": PLAYER_ACTION.RESUME

    };
    sendDatas(data);
    document.getElementById("punchButton").style.display = "inline-block";
    document.getElementById("resumeButton").style.display = "none";
}