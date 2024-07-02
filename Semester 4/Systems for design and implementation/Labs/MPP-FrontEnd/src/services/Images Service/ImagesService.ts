import axios from "axios";
import { endPointUrl } from "../config";

const apiEndPoint = endPointUrl + '/api/images';

export async function saveImage(image: File, userId: number) {
    const imageForm = new FormData();
    imageForm.append('image', image);
    imageForm.append('userId', userId.toString());

    await axios.post(apiEndPoint + '/saveImage', imageForm,
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
}

export async function getImageByUserId(userId: number): Promise<string> {
    const response = await axios.get(apiEndPoint + '/getImage/' + userId, 
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
    return response.data;
}