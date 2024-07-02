import { Routes } from '@angular/router';
import { LoginPageComponent } from './login-page/login-page.component';
import { SnakeBoardComponent } from './snake-board/snake-board.component';

export const routes: Routes = [
    {path: 'login', component: LoginPageComponent},
    {path: 'play', component: SnakeBoardComponent},
    {path: '**', redirectTo: '/login'}
];
