const DEBUG = true;

var SSE = new EventSource("/SSE");

SSE.onmessage = decodeSSEResponse;

function decodeMessage(msg) {
    if (msg[0] != '/')
        return [undefined, undefined];
    else
        msg = msg.slice(1)

    let data = msg.split('?');
    let type = data[0];
    let params = new Map();
    if (data[1] != undefined)
        for (let param of data[1].split('&'))
            params.set(param.split('=')[0], param.split('=')[1]);
    else
        params = undefined;
    return [type, params]
}

function decodeSSEResponse(event) {
    if (DEBUG) console.log("SSE: " + event.data);
    //event.data est de la forme type: /dataType?param1=value1&param2=value2...
    let [type, params] = decodeMessage(event.data);

    switch (type) {
        case "connectedPlayersList":
            if (document.title === "choix des joueurs")
                refreshPlayerDisplay(params.get("playerList"));
            else if (document.title === "Start" || document.title === "en attente")
                refreshPlayerPresence(params.get("playerList"));
                break;
        case "gameStarted":
            if (document.title === "en attente")
                if(params.get("gameMode") === "classic")
                redirect("/game_page.html");// window.location.href = "/game_page.html";
                else if(params.get("gameMode") === "infinite")
                redirect("/game_page_infini.html");// window.location.href = "/game_page_infini.html";
            break;
        case "goalTaken":
            if (document.title === "en jeu" || document.title === "en jeu (infini)")
                if (params.get("playerId") === localStorage.getItem("playerId").toString()) {
                    // un but a été pris, on cache le bouton tirer et on affiche le bouton reprendre
                    document.getElementById("punchButton").style.display = "none";
                    document.getElementById("resumeButton").style.display = "inline-block";
                }
            break;
        case "remainingLives":
            if (document.title === "en jeu")
                if (params.get("playerId") === localStorage.getItem("playerId").toString())
                    refreshLivesDisplay(params.get("lives"));
            break;
        case "gameEnded":
            if (document.title === "en jeu")
                window.location.href = "/score.html";
            break;

        default:
            if (DEBUG) console.log("unknown SSE response");
    }
}

function redirect(page)
{
    //on envoie une requete au serveur pour lui demander combien de joueurs sont en cours de redirection
    fetch("/redirectingAvailability?type=GET").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (text == "available")
        {
            if(DEBUG) console.log("redirecting to " + page);
            window.location.href = page;
        }
        else if (text == "busy")
        {
            if(DEBUG) console.log("retry to redirecting to " + page + " in 200ms");
            setTimeout(redirect, 200, page);
        }
    });
}