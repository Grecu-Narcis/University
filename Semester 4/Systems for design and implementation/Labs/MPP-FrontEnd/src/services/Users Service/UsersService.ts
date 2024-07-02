import axios from "axios";
import { User } from "../../models/user";
import { UserDTO } from "../../types/UserDTO.types";
import { saveImage } from "../Images Service/ImagesService";
import { endPointUrl } from "../config";

const apiEndPoint = endPointUrl + '/api/users';

export function convertDtoToUser(userToConvert: UserDTO) {
    return new User(userToConvert.id!, userToConvert.firstName, userToConvert.lastName, userToConvert.email, userToConvert.userRole);
}

export async function getUserById(requiredId: string) {
    const response = await axios.get(apiEndPoint + '/getUser/' + requiredId,
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
    return convertDtoToUser(response.data);
}

export async function getAllUsers() {
    try {
        const response = await axios.get(apiEndPoint + '/getAll', 
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );

        const users: UserDTO[] = response.data;
    
        return users;
    }
    catch (error) {
        return [];
    }
}

export async function getUsersPage(requiredPage: number, isAscending: boolean, pageSize: number = 6) {
    try {
    const response = await axios.get(apiEndPoint + '/getPage?page=' + requiredPage + "&isAscending=" + isAscending + "&pageSize=" + pageSize,
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
    const users: UserDTO[] = response.data;
    
    return users;
    } catch (error) {
        return [];  
    }   
}

export async function getUsersCount() {
    try {
        const response = await axios.get(apiEndPoint + '/countUsers', 
            {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
        );
        return response.data;
    }
    catch (error) {}
}

export async function addUser(userToAdd: UserDTO, profileImage?: File | undefined) {

    await axios.post(apiEndPoint + '/addUser', {
        ...userToAdd,
        // image: profileImage
    }, {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}})
    .then((response) => {
        console.log(response.data);

        if (!profileImage) return;
        saveImage(profileImage, response.data);
    });
}

export async function addMissingUsers(usersToAdd: UserDTO[]) {
    await axios.post(apiEndPoint + '/addUsers', usersToAdd, 
    {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}});
}

export async function updateUser(userToUpdate: UserDTO) {
    await axios.put(apiEndPoint + '/updateUser', {
        ...userToUpdate
    }, 
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
}

export async function deleteUser(userId: number) {
    await axios.delete(apiEndPoint + '/delete/' + userId, 
        {headers: {Authorization: 'Bearer ' + localStorage.getItem('authToken')}}
    );
}

export async function checkServerStatus() {
    console.log('Checking server status...');
    try {
        await axios.get(apiEndPoint + '/ping');
        return true;
    } catch (error) {
        return false;
    }
}