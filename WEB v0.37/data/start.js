function initStartPage() {
    fetch("/getPlayerList").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("PlayerListRequest: " + text);
        refreshPlayerPresence(text);
    });
}
function startGame(gameMode) {
    fetch("/startGame?gameMode=" + gameMode).then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("startGame: " + text);
        if (text != "ok") return;
        if (gameMode === "classic") {
            //window.location.href = "/game_page.html";
            redirect("/game_page.html");
        }
        if (gameMode === "infinite"){
             //window.location.href = "/game_page_infini.html";
            redirect("/game_page_infini.html");
        }
    });
}

function refreshPlayerPresence(connectedList) {
    let playersLogo = document.getElementById("playerPresenceDiv").children;
    if (DEBUG) console.log("connectedList: " + playersLogo.length);
    for (let i = 0; i < 4; i++) {
        if (connectedList[i] === "1") {
            playersLogo[i].style.opacity = 1;
        }
        else {
            playersLogo[i].style.opacity = 0.15;
        }
    }
}