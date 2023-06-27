function initScore() {

    // let text = "connectedPlayers:1000&lives:2,3,4,5";
    // updateScore(text);
    fetch("/getScores").then(function (response) {
        return response.text();
    }
    ).then(updateScore);
}

function updateScore(text) {
    if (DEBUG) console.log("getScores: " + text);
    let [connectedPlayers, lives] = text.split("&");

    //on verifie la validité des données
    if (connectedPlayers.split(":")[0] != "connectedPlayers" || lives.split(":")[0] != "lives") {
        if (DEBUG) console.log("getScores: invalid data");
        return;
    }
    connectedPlayers = connectedPlayers.split(":")[1];
    lives = lives.split(":")[1];
    lives = lives.split(",");
    if (DEBUG) console.log("getScores: " + connectedPlayers + " " + lives);

    let places = getScoreTable(connectedPlayers, lives);//les id dans l'ordre
    let scoreArea = document.getElementById("scoreboard");
    for (let i = 0; i < places.length; i++) {
        if (connectedPlayers[places[i]] === "1") {
            scoreArea.appendChild(createScoreElement(places[i], i, parseInt(lives[places[i]])));
        }
    }
}



function getScoreTable(connectedPlayers, lives) {
    //tri par insertion
    //on construit un tableau des places
    let places = [];
    let incr = 0;

    for (let i = 0; i < connectedPlayers.length; i++) {
        if (connectedPlayers[i] === "1") {
            places.push(i);
            incr++;
        }
    }
    if (DEBUG) console.log("construct places : " + places)
    for (let i = 1; i < incr; i++) {
        let j = i;
        while (j > 0 && parseInt(lives[places[j]]) > parseInt(lives[places[j - 1]])) {
            let tmp = places[j];
            places[j] = places[j - 1];
            places[j - 1] = tmp;
            j--;
        }
    }
    if (DEBUG) console.log("sorted places : " + places)
    return places;
}

function playerLogo(playerId) {
    let ret = document.createElement("img");
    ret.className = "logo-score";

    switch (playerId) {

        case 0:
            ret.src = "logo_bleu.png";
            break;
        case 1:
            ret.src = "logo_jaune.png";
            break;
        case 2:
            ret.src = "logo_rouge.png";
            break;
        case 3:
            ret.src = "logo_vert.png";
            break;
        default:
            return undefined;
    }
    return ret;
}

function quite() {
    document.location.href = "/";
}

function resetGame() {

    fetch("/resetGame").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("resetGame: " + text);

        document.location.href = "/index.html";
    });
}

function getScoreTxt(score) {
    let ret = document.createElement("p");
    ret.className = "scoreTxt";
    ret.innerHTML = "  " + String(score) + " vies restante" + (score > 1 ? "s" : "");
    return ret;
}

function createScoreElement(playerId, place, score) {
    let ret = document.createElement("article");
    let section1 = document.createElement("section");
    section1.className = "col";
    let span = document.createElement("span");
    span.className = "icon";
    let img = document.createElement("img");
    switch (place) {
        case 0:
            img.src = "trophee.png";
            break;
        case 1:
            img.src = "medaille-dargent.png";
            break;
        case 2:
            img.src = "medaille-de-bronze.png";
            break;
        default:
            img.src = "merde.png";
            break;
    }
    let section2 = document.createElement("section");
    section2.className = "row";
    section2.appendChild(playerLogo(playerId));
    section2.appendChild(getScoreTxt(score));

    span.appendChild(img);
    section1.appendChild(span);
    ret.appendChild(section1);
    ret.appendChild(section2);
    return ret;
}