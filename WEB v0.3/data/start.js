const DEBUG = true;

function startGame() {
    fetch("/startGame").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("startGame: " + text);
        if (text === "ok") window.location.href = "/game_page.html";
    });
}