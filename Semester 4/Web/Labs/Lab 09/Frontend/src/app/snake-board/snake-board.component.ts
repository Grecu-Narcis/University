import { Component, HostListener } from '@angular/core';
import { BackendService } from '../../services/BackendService';
import { Router } from '@angular/router';

@Component({
  selector: 'app-snake-board',
  standalone: true,
  imports: [],
  templateUrl: './snake-board.component.html',
  styleUrl: './snake-board.component.css'
})
export class SnakeBoardComponent {
  indexes: number[] = [];
  boardSize: number = 20;
  snake: number[][] = [];
  obstacles: number[][] = [];
  foodPosition: number[] = [];
  direction: number = 0;
  lastDirection: string = 'ArrowUp';
  private intervalId: any;
  lives: number = 3;

  constructor(private backendService: BackendService, private router: Router) {
    this.handleGameOver = this.handleGameOver.bind(this);
  }

  ngOnDestroy() {
    clearInterval(this.intervalId);
  }

  ngOnInit() {
    if (localStorage.getItem('userId') === null) {
      this.router.navigate(['/login']);
    }

    window.addEventListener('unload', this.handleGameOver);
    window.addEventListener('blur', this.handleGameOver);

    this.boardSize = 20;
    this.snake = this.createSnake();
    this.foodPosition = this.createFood();
    this.generateObstacles();
    this.direction = 0;

    this.indexes = Array.from({ length: this.boardSize }, (v, k) => k);

    this.intervalId = setInterval(() => {
      this.moveSnake();
    }, 300);
  }

  createSnake() {
    return [[10, 10]];
  }

  generateObstacles() {
    while (this.obstacles.length < 10) {
      let x = Math.floor(Math.random() * 20);
      let y = Math.floor(Math.random() * 20);

      if (this.isSnakeCell(x, y) || this.isFoodCell(x, y))
        continue;

      this.obstacles.push([x, y]);
    }
  }

  isSnakeCell(x: number, y: number) {
    return this.snake.some((cell) => cell[0] === x && cell[1] === y);
  }

  isFoodCell(x: number, y: number) {
    return this.foodPosition[0] === x && this.foodPosition[1] === y;
  }

  isObstacleCell(x: number, y: number) {
    return this.obstacles.some((cell) => cell[0] === x && cell[1] === y);
  }

  createFood() {
    let x = 0, y = 0;
    let isGood = false;
    while (!isGood) {
      isGood = true;

      x = Math.floor(Math.random() * 20);
      y = Math.floor(Math.random() * 20);

      if (this.isObstacleCell(x, y) || this.isSnakeCell(x, y))
        isGood = false;
    }
    
    return [x, y];
  }

  @HostListener('document:keydown', ['$event'])
  handleKeyPress(event: KeyboardEvent) {
    console.log(event.key);

    if (event.key == "ArrowUp" && (this.direction != 2 || this.snake.length == 1)) {
      this.direction = 0;
    }

    else if (event.key == "ArrowRight" && (this.direction != 3 || this.snake.length == 1)) {
      this.direction = 1;
    }

    else if (event.key == "ArrowDown" && (this.direction != 0 || this.snake.length == 1)) {
      this.direction = 2;
    }

    else if (event.key == "ArrowLeft" && (this.direction != 1 || this.snake.length == 1)) {
      this.direction = 3;
    }
  }

  moveSnake(): void {
    for (let i = this.snake.length - 1; i > 0; i--) 
      this.snake[i] = [...this.snake[i - 1]];

    let snakeHead: number[] = this.snake[0];

    if (this.direction === 0)  // UP
      this.snake[0][0] -= 1;

    else if (this.direction === 1)  // RIGHT
      this.snake[0][1] += 1;

    else if (this.direction === 2)  // DOWN
      this.snake[0][0] += 1;

    else 
      this.snake[0][1] -= 1;

    if (snakeHead[0] === this.foodPosition[0] && snakeHead[1] === this.foodPosition[1]) {
      this.foodPosition = this.createFood();
      let snakeTail = this.snake[this.snake.length - 1];
      let newPosition = [snakeTail[0], snakeTail[1]];
      this.snake.push(newPosition);
    }

    if (this.checkForGameOver()) {
      if (this.lives == 1)
        this.handleGameOver();
      else {
        this.lives -= 1;
        this.resetGame();
      }
    }

    this.handleMove();
  }

  checkForGameOver(): boolean {
    if (this.snake[0][0] >= this.boardSize || this.snake[0][0] < 0)
      return true;

    if (this.snake[0][1] >= this.boardSize || this.snake[0][1] < 0)
      return true;

    if (this.isObstacleCell(this.snake[0][0], this.snake[0][1]))
      return true;

    for (let i = 2; i < this.snake.length; i++)
      if (this.snake[i][0] === this.snake[0][0] && this.snake[i][1] === this.snake[0][1])
        return true;

    return false;
  }

  handleGameOver() {
    let startTime = parseInt(localStorage.getItem('startTime')!);
    let endTime = new Date().getTime();

    this.backendService.updateTimeSpent(Math.floor((endTime-startTime) / 1000)).subscribe();

    localStorage.clear();
    this.router.navigate(['/login']);
  }

  handleMove() {
    let moveDirection = 'Up';

    if (this.direction === 1)
      moveDirection = 'Right';
    
    else if (this.direction === 2)
      moveDirection = 'Down';

    else if (this.direction === 3) 
      moveDirection = 'Left';

    this.backendService.addMove(moveDirection).subscribe();
  }

  handleLogout() {
    localStorage.clear();
    this.handleGameOver();
  }

  resetGame() {
    this.snake = this.createSnake();
    this.foodPosition = this.createFood();
    this.generateObstacles();
    this.direction = 0;
  }
}
