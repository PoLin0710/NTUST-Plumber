//當前選擇水管區
var CURRENT_ID = 0;

//遊戲結束動畫
function showWinMessage() {
    $('#win-message').removeClass('hidden');
}

//設起點終點
function setPoint(Point, pointType) {
    if (pointType == "start")
        target = '#Faucet1';
    else
        target = '#flag';


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
            // 默认情况，可以根据需要设置
            break;
    }
}

//轉向水管
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
    pipe.addClass('rotate-animation'); // 添加旋转动画类
}

function createPipe(type, dir, id, flow, answer) {
    const pipe = $('<div></div>').addClass('pipe').attr('id', id);

    if (type == 1) {
        pipe.addClass('T-shape');
        pipe.html('<div class="row1"></div> <div class="row3"></div>');
    } else if (type == 2) {
        pipe.addClass('L-shape');
        pipe.html('<div class="row3"></div> <div class="row4"></div>');
    } else if (type == 3) {
        pipe.addClass('C-shape');
        pipe.html('<div class="row1"></div> <div class="row2"></div>');
    } else {
        pipe.addClass('S-shape'); // 默认为直线水管
        pipe.html('<div class="row2"></div>');
    }

    //是否有水流
    if (flow) {
        pipe.find('div').css('background-color', '#0099FF');//通道改藍色
    }

    //是否正解
    if (answer) {
        pipe.addClass("answer-bg");//加底
    }

    //轉向水管
    pipe_rotate(dir, pipe);

    return pipe;
}


$(document).ready(function () {
    var musicPlaying = false; // 初始状态为关闭声音
    //播放BGM
    $('#music').click(function () {
        // 切换音乐播放状态
        if (musicPlaying)
            pauseMusic();
        else
            playMusic();
    });

    function playMusic() {
        // 播放音乐
        $('#backgroundMusic').trigger('play');
        // 切换按钮样式
        $('#music').removeClass('off');

        musicPlaying = true;
    }

    function pauseMusic() {
        // 暂停音乐
        $('#backgroundMusic').trigger('pause');
        // 切换按钮样式
        $('#music').addClass('off');

        musicPlaying = false;
    }

    //*瀏覽器需先設為 音訊允許
    $('#music').click();

    //取得網址字串 http://127.0.0.1:5500/Frontend_Plumber/game.html?mode=1&M=0&N=0&fileName=map1.txt
    var url = location.href;
    //URLSearchParams 提取参数
    var urlParams = new URLSearchParams(url.split('?')[1]);
    // 獲取参数值
    var mode = urlParams.get('mode');
    var M = parseInt(urlParams.get('M'));
    var N = parseInt(urlParams.get('N'));
    var fileName = urlParams.get('fileName');

    var data = JSON.stringify({ mode: mode, M: M, N: N, fileName: fileName }); !

        //傳送地圖模式
        $.ajax({
            url: 'http://localhost:34568/start',
            method: 'POST',
            contentType: 'application/json',
            data: data,
            success: function (response) {
                console.log(response);

                // Board m*n
                const numRows = response.M; // m
                const numCols = response.N; // n
                const startPoint = response.begin;//起點
                const endPoint = response.end//終點
                const win_statu = response.win_statu;//是否通關
                const PIPES = response.PIPES;//水管盤
                const current_id = response.current_id;//當前選取位置
                CURRENT_ID = current_id;


                if (!win_statu) {
                    //初始化地圖版面
                    const pipeBoard = $('#pipeBoard');
                    var index_id = 0;

                    for (let i = 0; i < numRows; i++) {
                        const row = $('<div></div>').addClass('row');
                        for (let j = 0; j < numCols; j++) {
                            const pipeID = PIPES[index_id].id; //水管id
                            const pipeType = PIPES[index_id].type; //水管種類
                            const pipeDir = PIPES[index_id].dir; //水管方向
                            const pipeFlow = PIPES[index_id].flow; //水流
                            const pipeAnswer = PIPES[index_id].answer; //正解

                            const pipe = createPipe(pipeType, pipeDir, pipeID, pipeFlow, pipeAnswer);

                            row.append(pipe);

                            index_id++;
                        }

                        pipeBoard.append(row);
                    }

                    $(`#` + current_id).addClass("red-border");//加紅框

                    //設起點終點
                    setPoint(startPoint, "start");
                    setPoint(endPoint, "end");
                }
            },
            error: function (xhr, ajaxOptions, thrownError) {
                let err = ajaxOptions + " " + thrownError;
                console.warn(err);
            }
        });

    //觸發鍵盤操作
    $(document).keydown(function (e) {
        var move;
        var ismove;
        switch (e.which) {
            case 87: // W键
                move = 'w';
                ismove = true;
                break;
            case 83: // S键
                move = 's';
                ismove = true;
                break;
            case 65: // A键
                move = 'a';
                ismove = true;
                break;
            case 68: // D键
                move = 'd';
                ismove = true;
                break;
            case 74: // J键
                move = 'j';
                ismove = false;

                //水管旋轉動畫(向左)
                var pipe = $('#' + CURRENT_ID);
                pipe.addClass('rotate-left-animation');

                break;
            case 76: // L键
                move = 'l';
                ismove = false;

                //水管旋轉動畫(向右)
                var pipe = $('#' + CURRENT_ID);
                pipe.addClass('rotate-right-animation');

                break;

            default: return; // 如果按下的键不是WASD，则不执行任何操作
        }
        e.preventDefault(); // 防止浏览器默认事件

        if (ismove) {
            //wasd ajax
            var data = JSON.stringify({ move: move });

            $.ajax({
                url: 'http://localhost:34568/move',
                method: 'POST',
                contentType: 'application/json',
                data: data,
                success: function (response) {
                    console.log(response);

                    const numRows = response.M; // m
                    const numCols = response.N; // n
                    const win_statu = response.win_statu;//是否通關
                    const PIPES = response.PIPES;//水管盤
                    const current_id = response.current_id;//當前選取位置
                    CURRENT_ID = current_id;

                    if (!win_statu) {
                        var index_id = 0;
                        const pipeBoard = $('#pipeBoard');
                        //清空pipeBoard
                        pipeBoard.empty();

                        for (let i = 0; i < numRows; i++) {
                            const row = $('<div></div>').addClass('row');
                            for (let j = 0; j < numCols; j++) {
                                const pipeID = PIPES[index_id].id; //水管id
                                const pipeType = PIPES[index_id].type; //水管種類
                                const pipeDir = PIPES[index_id].dir; //水管方向
                                const pipeFlow = PIPES[index_id].flow; //水流
                                const pipeAnswer = PIPES[index_id].answer; //正解
                                const pipe = createPipe(pipeType, pipeDir, pipeID, pipeFlow, pipeAnswer);

                                row.append(pipe);

                                index_id++;
                            }

                            pipeBoard.append(row);
                        }

                        $(`#` + current_id).addClass("red-border");//加紅框
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
                    console.log(response);

                    //轉動音效
                    $('#turnMusic').trigger('play');
                    $('#turnMusic').volume = 1;

                    const numRows = response.M; // m
                    const numCols = response.N; // n
                    const win_statu = response.win_statu;//是否通關
                    const PIPES = response.PIPES;//水管盤
                    const current_id = response.current_id;//當前選取位置
                    CURRENT_ID = current_id;


                    var index_id = 0;
                    const pipeBoard = $('#pipeBoard');
                    //清空pipeBoard
                    pipeBoard.empty();

                    for (let i = 0; i < numRows; i++) {
                        const row = $('<div></div>').addClass('row');
                        for (let j = 0; j < numCols; j++) {
                            const pipeID = PIPES[index_id].id; //水管id
                            const pipeType = PIPES[index_id].type; //水管種類
                            const pipeDir = PIPES[index_id].dir; //水管方向
                            const pipeFlow = PIPES[index_id].flow; //水流
                            const pipeAnswer = PIPES[index_id].answer; //正解
                            const pipe = createPipe(pipeType, pipeDir, pipeID, pipeFlow, pipeAnswer);// (type, dir, id, flow, answer);

                            row.append(pipe);

                            index_id++;
                        }
                        pipeBoard.append(row);
                    }
                    $(`#` + current_id).addClass("red-border");//加紅框

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
