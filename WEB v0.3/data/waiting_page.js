const DEBUG = true;

var source = new EventSource("/getGameStarted_SSE");

function initWaitingPage() {
    gamesStartedSSE();
}
function endWaitingPage() {
    // on ferme les SSE
    source.close();
}
function gamesStartedSSE()
{
    source.onmessage = function (event) {
        if (DEBUG) console.log("GameStartedSSE: " + event.data);
        window.location.href = "/game_page.html";
    }

    source.onerror = function (event) {
        if (DEBUG) console.log("GameStartedSSE: " + event.data);
    }
}