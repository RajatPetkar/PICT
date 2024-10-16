const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const boxSize = 20;  

class Snake {
    constructor() {
        this.body = [{ x: 9 * boxSize, y: 10 * boxSize }]; 
        this.direction = 'RIGHT';                           
        this.newDirection = 'RIGHT';
    }

    update() {
        const head = { ...this.body[0] };

        switch (this.newDirection) {
            case 'LEFT': head.x -= boxSize; break;
            case 'UP': head.y -= boxSize; break;
            case 'RIGHT': head.x += boxSize; break;
            case 'DOWN': head.y += boxSize; break;
        }

        this.body.unshift(head);

        if (head.x === food.position.x && head.y === food.position.y) {
            food.generate(); 
        } else {
            this.body.pop();  
        }

        this.direction = this.newDirection;  
    }

    draw() {
        ctx.fillStyle = 'lime';
        this.body.forEach(part => {
            ctx.fillRect(part.x, part.y, boxSize, boxSize);
        });
    }

    hasCollision() {
        const head = this.body[0];

        if (head.x < 0 || head.x >= canvas.width || head.y < 0 || head.y >= canvas.height) {
            return true;
        }

        for (let i = 1; i < this.body.length; i++) {
            if (head.x === this.body[i].x && head.y === this.body[i].y) {
                return true;
            }
        }

        return false;
    }

    changeDirection(newDirection) {
        const oppositeDirections = {
            LEFT: 'RIGHT',
            RIGHT: 'LEFT',
            UP: 'DOWN',
            DOWN: 'UP'
        };

        if (newDirection !== oppositeDirections[this.direction]) {
            this.newDirection = newDirection;
        }
    }
}

class Food {
    constructor() {
        this.position = { x: 0, y: 0 };
        this.generate(); 
    }

    generate() {
        const rows = canvas.width / boxSize;
        const cols = canvas.height / boxSize;
        this.position.x = Math.floor(Math.random() * rows) * boxSize;
        this.position.y = Math.floor(Math.random() * cols) * boxSize;
    }

    draw() {
        ctx.fillStyle = 'red';
        ctx.fillRect(this.position.x, this.position.y, boxSize, boxSize);
    }
}

let snake = new Snake();
let food = new Food();

function gameLoop() {
    if (snake.hasCollision()) {
        alert('Game Over!');
        snake = new Snake(); 
        food = new Food();   
    }

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    snake.update();
    snake.draw();
    food.draw();

    setTimeout(gameLoop, 100);
}

window.addEventListener('keydown', (event) => {
    const keyDirectionMap = {
        'ArrowLeft': 'LEFT',
        'ArrowUp': 'UP',
        'ArrowRight': 'RIGHT',
        'ArrowDown': 'DOWN'
    };
    const newDirection = keyDirectionMap[event.key];
    if (newDirection) {
        snake.changeDirection(newDirection);
    }
});

gameLoop();
