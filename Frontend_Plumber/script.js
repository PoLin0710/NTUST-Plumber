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

function pipeDir(dir, pipe) {
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
}
function changePipe(type, dir, id, flow, answer) {
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
        pipe.html('<div class="row1"></div>');
    }

    //是否水流
    var folw_bool = flow;
    if (folw_bool) {
        pipe.find('div').css('background-color', '#0099FF');//通道改藍色
    }

    //是否正解
    var answer_bool = answer;
    if (answer_bool) {
        pipe.addClass("answer-bg");//加灰底
    }

    pipeDir(dir, pipe);

    pipe.on('click', function () {
        pipeDir(3, pipe);
    });

    return pipe;
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
        pipe.html('<div class="row1"></div>');
    }

    //是否水流
    var folw_bool = flow;
    if (folw_bool) {
        pipe.find('div').css('background-color', '#0099FF');//通道改藍色
    }

    //是否正解
    var answer_bool = answer;
    if (answer_bool) {
        pipe.addClass("answer-bg");//加灰底
    }

    pipeDir(dir, pipe);

    pipe.on('click', function () {
        pipeDir(3, pipe);
    });

    return pipe;
}

$(document).ready(function () {
    //home
    //ajax post 1 2 3
    var mapType = 1;
    //return
    // 取網址
    //取得網址字串 ?userid
    var url = location.href;
    //尋找網址列中是否有資料傳遞(QueryString)
    if (url.indexOf('?') != -1) {
        //從?切2半放進ary中，ary[0] = 'http://localhost:54987/Management/Account/Detail'，ary[1] = 'userid=P0000'
        //再從 = 切，ary[0] = 'userid'，ary[1] = 'P0000'
        var mapType = url.split('?')[1].split('=')[1];//=1
        console.log(mapType);
    }




    var gameOver = false;
    if (!gameOver) {

        // Board m*n
        const numRows = 6; // m
        const numCols = 6; // n
        const pipeBoard = $('#pipeBoard');


        //pipeBoard[水管種類,方向]->[type,dir]=[0,0]
        // pipeBoard=[];//接資料
        // pipeBoard.id=0
        // pipeBoard.type=3;
        // pipeBoard.dir=1;
        //pipeBoard.flow=true;

        var pipeBoard_id = 0;
        for (let i = 0; i < numRows; i++) {
            const row = $('<div></div>').addClass('row');
            for (let j = 0; j < numCols; j++) {
                const randomnum1 = Math.floor(Math.random() * 5);
                const randomnum2 = Math.floor(Math.random() * 5);
                //const newPipe = createPipe(type, dir, id, flow, answer);
                const pipe = createPipe(randomnum1, randomnum2, pipeBoard_id, randomnum2, randomnum2);//type, dir,id ,flow,answer
                row.append(pipe);
                pipeBoard_id++;
            }
            pipeBoard.append(row);
        }

        // Set start and end points
        //設起點終點
        const startPoint = 5;
        const endPoint = 2;
        setPoint(startPoint, "start");
        setPoint(endPoint, "end");


        //觸發wasd
        $(document).keydown(function (e) {
            var direction;
            switch (e.which) {
                case 87: // W键
                    direction = 0;
                    break;
                case 83: // S键
                    direction = 1;
                    break;
                case 65: // A键
                    direction = 2;
                    break;
                case 68: // D键
                    direction = 3;
                    break;
                case 74: // J键
                    direction = 4;
                    location.reload();
                    break;
                case 76: // L键
                    direction = 5;
                    var gameOver = false;
                    if (!gameOver) {
                        var id = 5
                        const randomnum1 = Math.floor(Math.random() * 5);
                        const randomnum2 = Math.floor(Math.random() * 5);
                        // 获取要替换的元素
                        const existingElement = $('#' + id);
                        //const newPipe = createPipe(type, dir, id, flow, answer);
                        const newPipe = createPipe(randomnum1, randomnum2, id, randomnum2, randomnum2);//type, dir,id ,flow,answer
                        // 替换现有元素
                        existingElement.replaceWith(newPipe);
                    } else {
                        //結束遊戲成功 
                        //回主畫面 

                    }
                    break;

                default: return; // 如果按下的键不是WASD，则不执行任何操作
            }
            e.preventDefault(); // 防止浏览器默认事件

            //wasd ajax

            //return 
            var current_id = 3; //改
            var current_id_target = `#` + current_id;
            $(current_id_target).addClass("red-border");//加紅框

            //JL ajax

            //return 改
            // var gameOver = false;
            // if (!gameOver) {

            //     // 获取要替换的元素
            //     const existingElement = $('#' + id);
            //     //const newPipe = createPipe(type, dir, id, flow, answer);
            //     const pipe = createPipe(randomnum1, randomnum2, pipeBoard_id, randomnum2, randomnum2);//type, dir,id ,flow,answer
            //     // 替换现有元素
            //     existingElement.replaceWith(newPipe);


            // } else {
            //     //結束遊戲成功 
            //     //回主畫面 

            // }

        });

    } else {
        //結束遊戲成功 
        //回主畫面 
        window.location.href = "index.html";



    }


    //////////
});
