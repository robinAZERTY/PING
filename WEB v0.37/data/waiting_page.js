function initWaitingPage() {
    fetch("/getPlayerList").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("PlayerListRequest: " + text);
        refreshPlayerPresence(text);
    });

}


function refreshPlayerPresence(connectedList) {
    let playersLogo = document.getElementById("playerPresenceDiv").children;
    if (DEBUG) console.log("connectedList: " + playersLogo.length);
    for (let i = 0; i < 4; i++) {
        if(connectedList[i]==="1"){
            playersLogo[i].style.opacity = 1;
        }
        else{
            playersLogo[i].style.opacity = 0.15;
        }
    }
}