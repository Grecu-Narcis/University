import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { SnakeBoardComponent } from "./snake-board/snake-board.component";
import { BackendService } from '../services/BackendService';
import { HttpClient, HttpClientModule } from '@angular/common/http';
import { LoginPageComponent } from "./login-page/login-page.component";

@Component({
    selector: 'app-root',
    standalone: true,
    templateUrl: './app.component.html',
    styleUrl: './app.component.css',
    providers: [BackendService],
    imports: [RouterOutlet, SnakeBoardComponent, HttpClientModule, LoginPageComponent]
})
export class AppComponent {
  title = 'Lab8';
}
