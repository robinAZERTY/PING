function initScore()
{

    // let [lives, places] = constructScoreTable();

    // // display the score
    // let scoreArea = document.getElementsByClassName("forme");
    // for (let i = 0; i < 4; i++)
    //     {
    //         scoreArea[i].appendChild(playerLogo(places[i]));
    //         scoreArea[i].appendChild(document.createTextNode(String(lives[places[i]]) + " vies restantes"));
    //     }
    
    fetch("/getLiveList").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("getLiveList: " + text);
        let lives = text.split(",");
        let places = getScoreTable(lives);//les id dans l'ordre
        let scoreArea = document.getElementsByClassName("forme");
        for (let i = 0; i < 4; i++)
        {
            scoreArea[i].appendChild(playerLogo(places[i]));
            scoreArea[i].appendChild(document.createTextNode("  "+ String(lives[places[i]]) + " vies restantes"));
        }
    });
}

    

function getScoreTable(lives){
    // compute the place of each player
    // let places = [];
    // for (let i = 0; i < 4; i++)
    // {
    //     let place = 0;
    //     for (let j = 0; j < 4; j++)
    //     {
    //         if (parseInt(lives[i]) < parseInt(lives[j]))
    //         {
    //             place++;
    //         }
    //     }
    //     places[i] = place;
    // }

    //tri par insertion
    let places = [0,1,2,3];
    for (let i = 1; i < 4; i++)
    {
        let j = i;
        while (j > 0 && parseInt(lives[places[j]]) > parseInt(lives[places[j-1]]))
        {
            let tmp = places[j];
            places[j] = places[j-1];
            places[j-1] = tmp;
            j--;
        }
    }
    return places;
}

function playerLogo(playerId)
{
    return document.createTextNode("Joueur " + String(playerId));
}

function quite()
{
    document.location.href = "/";
}

function resetGame()
{

    fetch("/resetGame").then(function (response) {
        return response.text();
    }
    ).then(function (text) {
        if (DEBUG) console.log("resetGame: " + text);

    document.location.href = "/index.html"; 
    });
}