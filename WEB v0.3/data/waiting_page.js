const DEBUG = true;

function initWaitingPage() {
    gamesStartedSSE();
}

function gamesStartedSSE()
{
    var source = new EventSource("/getGameStarted_SSE");
    source.onmessage = function (event) {
        if (DEBUG) console.log("GameStartedSSE: " + event.data);
        window.location.href = "/game_page.html";
    }

    source.onerror = function (event) {
        if (DEBUG) console.log("GameStartedSSE: " + event.data);
    }
}