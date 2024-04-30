// Current selected pipe area
var CURRENT_ID = 0;

// Show win message animation
function showWinMessage() {
    $('#win-message').removeClass('hidden');
}

// Set start and end points
function setPoint(Point, pointType) {
    if (pointType == "start")
        target = '#Faucet1';
    else
        target = '#flag';


    // set the point position
    switch (Point) {
        case 0:
            $(target).css({
                top: $('#Board .row:first-child .pipe:first-child').position().top - $('#Faucet1').height() - 10,
                left: $('#Board .row:first-child .pipe:first-child').position().left + ($('#Board .row:first-child .pipe:first-child').width() / 2) - ($('#Faucet1').width() / 2)
            });
            break;
        case 1:
            $(target).css({
                top: $('#Board .row:first-child .pipe:last-child').position().top - $('#Faucet1').height() - 10,
                left: $('#Board .row:first-child .pipe:last-child').position().left + ($('#Board .row:first-child .pipe:last-child').width() / 2) - ($('#Faucet1').width() / 2)
            });
            break;
        case 2:
            $(target).css({
                top: $('#Board .row:first-child .pipe:last-child').position().top + ($('#Board .row:first-child .pipe:last-child').height() / 2) - ($('#Faucet1').height() / 2),
                left: $('#Board .row:first-child .pipe:last-child').position().left + $('#Board .row:first-child .pipe:last-child').width() + 10
            });
            break;
        case 3:
            $(target).css({
                top: $('#Board .row:last-child .pipe:last-child').position().top + ($('#Board .row:last-child .pipe:last-child').height() / 2) - ($('#Faucet1').height() / 2),
                left: $('#Board .row:last-child .pipe:last-child').position().left + $('#Board .row:last-child .pipe:last-child').width() + 10
            });
            break;
        case 4:
            $(target).css({
                top: $('#Board .row:last-child .pipe:last-child').position().top + $('#Board .row:last-child .pipe:last-child').height() + 10,
                left: $('#Board .row:last-child .pipe:last-child').position().left + ($('#Board .row:last-child .pipe:last-child').width() / 2) - ($('#Faucet1').width() / 2)
            });
            break;
        case 5:
            $(target).css({
                top: $('#Board .row:last-child .pipe:first-child').position().top + $('#Board .row:last-child .pipe:first-child').height() + 10,
                left: $('#Board .row:last-child .pipe:first-child').position().left + ($('#Board .row:last-child .pipe:first-child').width() / 2) - ($('#Faucet1').width() / 2)
            });
            break;
        case 6:
            $(target).css({
                top: $('#Board .row:last-child .pipe:first-child').position().top + ($('#Board .row:last-child .pipe:first-child').height() / 2) - ($('#Faucet1').height() / 2),
                left: $('#Board .row:last-child .pipe:first-child').position().left - $('#Faucet1').width() - 10
            });
            break;
        case 7:
            $(target).css({
                top: $('#Board .row:first-child .pipe:first-child').position().top + ($('#Board .row:first-child .pipe:first-child').height() / 2) - ($('#Faucet1').height() / 2),
                left: $('#Board .row:first-child .pipe:first-child').position().left - $('#Faucet1').width() - 10
            });
            break;
        default:
            //Default, can be set as needed
            break;
    }
}

// Rotate pipes
function pipe_rotate(dir, pipe) {
    switch (dir) {
        case 1:
            pipe.css('transform', 'rotate(90deg)');
            break;
        case 2:
            pipe.css('transform', 'rotate(180deg)');
            break;
        case 3:
            pipe.css('transform', 'rotate(270deg)');
            break;
        default:
            break;
    }

    // Add rotation animation 
    pipe.addClass('rotate-animation');
}

// Create pipe elements
function createPipe(type, dir, id, flow, answer) {
    const pipe = $('<div></div>').addClass('pipe').attr('id', id);

    if (type == 1) {
        pipe.addClass('T-shape');//The default is T-type pipe
        pipe.html('<div class="row1"></div> <div class="row3"></div>');
    } else if (type == 2) {
        pipe.addClass('L-shape');//The default is L-type pipe
        pipe.html('<div class="row3"></div> <div class="row4"></div>');
    } else if (type == 3) {
        pipe.addClass('C-shape');//The default is cross shape pipe
        pipe.html('<div class="row1"></div> <div class="row2"></div>');
    } else {
        pipe.addClass('S-shape'); //The default is straight pipe
        pipe.html('<div class="row2"></div>');
    }

    //have flow
    if (flow) {
        pipe.find('div').css('background-color', '#0099FF');//通道改藍色
    }

    //is answer
    if (answer) {
        pipe.addClass("answer-bg");//加底
    }

    //rotate pipe
    pipe_rotate(dir, pipe);

    return pipe;
}


$(document).ready(function () {
    // Initial state: sound is off
    var musicPlaying = false;

    //toggle background music
    $('#music').click(function () {
        // Toggle music play state
        if (musicPlaying)
            pauseMusic();
        else
            playMusic();
    });

    //play background music
    function playMusic() {
        // Play music
        $('#backgroundMusic').trigger('play');
        // Toggle button style
        $('#music').removeClass('off');

        musicPlaying = true;
    }

    //pause background music
    function pauseMusic() {
        // Play music
        $('#backgroundMusic').trigger('play');
        // Toggle button style
        $('#music').removeClass('off');

        musicPlaying = false;
    }

    // *First Set browser to allow audio
    $('#music').click();

    // Get URL parameters for mode, M, N, and fileName and Send to backend
    // http://127.0.0.1:5500/Frontend_Plumber/game.html?mode=1&M=0&N=0&fileName=map1.txt
    var url = location.href;
    //split URL to get URLSearchParams 
    var urlParams = new URLSearchParams(url.split('?')[1]);
    // get parameter
    var mode = urlParams.get('mode');
    var M = parseInt(urlParams.get('M'));
    var N = parseInt(urlParams.get('N'));
    var fileName = urlParams.get('fileName');

    var data = JSON.stringify({ mode: mode, M: M, N: N, fileName: fileName }); !

        //send map mode
        $.ajax({
            url: 'http://localhost:34568/start',
            method: 'POST',
            contentType: 'application/json',
            data: data,
            success: function (response) {
                //pipe board 
                const numRows = response.M; // Number of rows (m)
                const numCols = response.N; // Number of columns (n)
                const startPoint = response.begin; // Start point
                const endPoint = response.end; // End point
                const win_statu = response.win_statu; // Win status (whether completed)
                const PIPES = response.PIPES; // Pipe grid
                const current_id = response.current_id; // Current selected id
                CURRENT_ID = current_id; // Update current ID

                if (!win_statu) {
                    // Initialize the map board
                    const pipeBoard = $('#pipeBoard');
                    var index_id = 0;

                    for (let i = 0; i < numRows; i++) {
                        const row = $('<div></div>').addClass('row');

                        for (let j = 0; j < numCols; j++) {
                            const pipeID = PIPES[index_id].id; // Pipe ID
                            const pipeType = PIPES[index_id].type; // Pipe type
                            const pipeDir = PIPES[index_id].dir; // Pipe direction
                            const pipeFlow = PIPES[index_id].flow; // Pipe flow
                            const pipeAnswer = PIPES[index_id].answer; // Correct answer

                            //create new pipe element
                            const pipe = createPipe(pipeType, pipeDir, pipeID, pipeFlow, pipeAnswer);

                            //append to row
                            row.append(pipe);

                            index_id++;
                        }
                        //append to pipeBoard 
                        pipeBoard.append(row);
                    }

                    //current pipe add red border
                    $(`#` + current_id).addClass("red-border");

                    // Set start and end points
                    setPoint(startPoint, "start");
                    setPoint(endPoint, "end");
                }

            },
            error: function (xhr, ajaxOptions, thrownError) {
                let err = ajaxOptions + " " + thrownError;
                console.warn(err);
            }
        });

    // Keyboard operation triggers
    $(document).keydown(function (e) {
        var move;
        var ismove;

        switch (e.which) {
            case 87: // W key
                move = 'w';
                ismove = true;
                break;
            case 83: // S key
                move = 's';
                ismove = true;
                break;
            case 65: // A key
                move = 'a';
                ismove = true;
                break;
            case 68: // D key
                move = 'd';
                ismove = true;
                break;
            case 74: // J key
                move = 'j';
                ismove = false;

                // Rotate pipe animation (left)
                var pipe = $('#' + CURRENT_ID);
                pipe.addClass('rotate-left-animation');

                break;
            case 76: // L key
                move = 'l';
                ismove = false;

                // Rotate pipe animation (right)
                var pipe = $('#' + CURRENT_ID);
                pipe.addClass('rotate-right-animation');

                break;

            default: return; // If the pressed key is not WASD, do nothing
        }
        e.preventDefault(); // Prevent default browser event

        if (ismove) {
            //wasd ajax
            var data = JSON.stringify({ move: move });

            $.ajax({
                url: 'http://localhost:34568/move',
                method: 'POST',
                contentType: 'application/json',
                data: data,
                success: function (response) {
                    const numRows = response.M; // Number of rows (m)
                    const numCols = response.N; // Number of columns (n)
                    const win_statu = response.win_statu; // Whether the game is won
                    const PIPES = response.PIPES; // Pipe grid
                    const current_id = response.current_id; // Current selection position
                    CURRENT_ID = current_id;

                    if (!win_statu) {
                        var index_id = 0;
                        const pipeBoard = $('#pipeBoard');

                        // Clear pipeBoard
                        pipeBoard.empty();

                        for (let i = 0; i < numRows; i++) {
                            const row = $('<div></div>').addClass('row');

                            for (let j = 0; j < numCols; j++) {
                                const pipeID = PIPES[index_id].id; // Pipe ID
                                const pipeType = PIPES[index_id].type; // Pipe type
                                const pipeDir = PIPES[index_id].dir; // Pipe direction
                                const pipeFlow = PIPES[index_id].flow; // Pipe flow
                                const pipeAnswer = PIPES[index_id].answer; // Correct answer
                                const pipe = createPipe(pipeType, pipeDir, pipeID, pipeFlow, pipeAnswer);

                                row.append(pipe);

                                index_id++;
                            }

                            pipeBoard.append(row);
                        }

                        $(`#` + current_id).addClass("red-border"); // Add red border
                    }
                },
                error: function (xhr, ajaxOptions, thrownError) {
                    let err = ajaxOptions + " " + thrownError;
                    console.warn(err);
                }

            });
        } else {
            //JL ajax
            var data = JSON.stringify({ turn: move });

            $.ajax({
                url: 'http://localhost:34568/turn',
                method: 'POST',
                contentType: 'application/json',
                data: data,
                success: function (response) {
                    // Sound effect for rotation
                    $('#turnMusic').trigger('play');
                    $('#turnMusic').volume = 1;

                    const numRows = response.M; // Number of rows (m)
                    const numCols = response.N; // Number of columns (n)
                    const win_statu = response.win_statu; // Whether the game is won
                    const PIPES = response.PIPES; // Pipe grid
                    const current_id = response.current_id; // Current selection position
                    CURRENT_ID = current_id;

                    var index_id = 0;
                    const pipeBoard = $('#pipeBoard');

                    // Clear pipeBoard
                    pipeBoard.empty();

                    for (let i = 0; i < numRows; i++) {
                        const row = $('<div></div>').addClass('row');

                        for (let j = 0; j < numCols; j++) {
                            const pipeID = PIPES[index_id].id; // Pipe ID
                            const pipeType = PIPES[index_id].type; // Pipe type
                            const pipeDir = PIPES[index_id].dir; // Pipe direction
                            const pipeFlow = PIPES[index_id].flow; // Pipe flow
                            const pipeAnswer = PIPES[index_id].answer; // Correct answer

                            const pipe = createPipe(pipeType, pipeDir, pipeID, pipeFlow, pipeAnswer);

                            row.append(pipe);

                            index_id++;
                        }
                        pipeBoard.append(row);
                    }
                    $(`#` + current_id).addClass("red-border"); // Add red border

                    if (win_statu) {
                        showWinMessage();
                        $(document).off('keydown');
                        $('#homeButton').hide();
                        $('#music').hide();
                        $('#music_close').hide();
                    }
                },
                error: function (xhr, ajaxOptions, thrownError) {
                    let err = ajaxOptions + " " + thrownError;
                    console.warn(err);
                }

            });
        }
    });
});
