import axios from "axios";
import { endPointUrl } from "../config";

const apiEndPoint = endPointUrl + '/api/location';

export async function updateDealerLocation(dealerId: number, latitude: number, longitude: number) {
    await axios.put(apiEndPoint + '/update', 
        {
            dealerId: dealerId,
            latitude: latitude,
            longitude: longitude
        }, 

        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
}

export async function getDealerLocation(userId: number) {    
    return await axios.get(apiEndPoint + '/get/' + userId,
        // {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
}