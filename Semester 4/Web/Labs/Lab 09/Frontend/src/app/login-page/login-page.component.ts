import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { BackendService } from '../../services/BackendService';

@Component({
  selector: 'app-login-page',
  standalone: true,
  imports: [FormsModule],
  templateUrl: './login-page.component.html',
  styleUrl: './login-page.component.css'
})
export class LoginPageComponent {
  username: string = '';
  password: string = '';

  constructor(private backendService: BackendService, private router: Router) {}

  handleLogin() {
    this.backendService.loginUser(this.username, this.password).subscribe(
      (response) => { 
        if (response.status === 200) {
          let currentDate = new Date();

          localStorage.setItem('userId', response.body!.userId.toString());
          localStorage.setItem('startTime', (currentDate.getTime()).toString());
          this.router.navigate(['/play']);
        }

        else {
          alert(response.body);
        }
      }
    )
  }
}

