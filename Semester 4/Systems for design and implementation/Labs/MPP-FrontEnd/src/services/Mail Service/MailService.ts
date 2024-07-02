import axios from "axios";
import { endPointUrl } from "../config";

const apiEndPoint = endPointUrl + '/api/mail';

export async function sendMail(userName: string, userEmail: string, message: string, destination: string) {
    await axios.post(apiEndPoint + '/send', 
        {
            userName: userName,
            userEmail: userEmail,
            message: message,
            destination: destination
        },
    {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}});
}
