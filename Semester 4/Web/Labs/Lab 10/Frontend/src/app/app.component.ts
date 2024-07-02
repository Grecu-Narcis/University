import { Component } from '@angular/core';
import { RouterOutlet, RouterModule } from '@angular/router';
import { BackendService } from '../services/BackendService';
import { HttpClientModule } from '@angular/common/http';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, RouterModule, HttpClientModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css',
  providers: [BackendService]
})
export class AppComponent {
  title = 'Lab07-FrontEnd';
}
