const DEBUG = true;

var source = new EventSource("/getConnectedPlayerSSE");

function initPlayerChoiceHTML()
{
    getConnectedPlayer();
    getConnectedPlayerSSE();
}

function endPlayerChoice()
{
    // on ferme les SSE
    
    source.close();
}

//
function getConnectedPlayer()
{
    fetch("/getPlayerList").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("PlayerChoiceRequest: " + text);
        refreshPlayerDisplay(text);
    });
}

function getConnectedPlayerSSE()
{
    source.onmessage = function (event) {
        if (DEBUG) console.log("ConnectedPlayerSSE: " + event.data);
        refreshPlayerDisplay(event.data);
    }

    source.onerror = function (event) {
        if (DEBUG) console.log("ConnectedPlayerSSE: " + event.data);
    }
    
    
}

//fonction de configuration des requetes
function onChoice(PlayerId)
{
    //send request to server and wait for text response
    fetch("/PlayerChoice?playerId=" + String(PlayerId)).then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("PlayerChoiceRequest: " + text);

        if (text === "refused"){
            alert("Ce joueur est déjà pris");
        }
        else if (text === "first"){
            localStorage.setItem("playerId", PlayerId);
            window.location.href = "/start.html";
        }
        else if (text === "accepted"){
            localStorage.setItem("playerId", PlayerId);
            window.location.href = "/waiting_page.html";
        }
        else 
        {
            alert("Erreur lors de la requete");
        }
    });
}

function refreshPlayerDisplay(PlayerList_str)
{
    //mettre à l'affichage des boutons en fonction de PlayerList_str (ex: 0101)
    //si 1, bouton transparent (opacité à 0.3) et disabled
    //si 0, bouton normal (opacité à 1) et enabled

    for (var i = 0; i < PlayerList_str.length; i++)
    {
        var button = document.getElementsByClassName("btn");
        if (PlayerList_str[i] === "1")
        {
            button[i].style.opacity = "0.3";
            button[i].disabled = true;
        }
        else
        {
            button[i].style.opacity = "1";
            button[i].disabled = false;
        }
    }

}