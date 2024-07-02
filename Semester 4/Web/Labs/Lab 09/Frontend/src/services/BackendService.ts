import { HttpClient } from "@angular/common/http";
import { Injectable } from "@angular/core";

const endPoint = 'http://localhost:8080/api';

@Injectable({
    providedIn: 'root'
})
export class BackendService {
    constructor(private http: HttpClient) {}

    public addMove(moveDirection: string) {
        const userId = parseInt(localStorage.getItem('userId')!);

        return this.http.post(endPoint + '/game/addMove', {
            'userId': userId,
            'moveDirection': moveDirection
        });
    }

    public updateTimeSpent(timeSpent: number) {
        const userId = parseInt(localStorage.getItem('userId')!);

        return this.http.put(endPoint + '/game/updateTimeSpent', {
            'userId': userId,
            'newTime': timeSpent
        });
    }

    public loginUser(username: string, password: string) {
        return this.http.post<LoginResponse>(endPoint + '/auth/login', {
            'username': username,
            'password': password
        }, {observe: 'response'});
    }
}

type LoginResponse = {
    userId: number
}