import axios from "axios";
import { LoginResponseDTO } from "../../types/LoginResponseDTO.types";
import { endPointUrl } from "../config";

const apiEndpoint = endPointUrl + '/api/auth';

export async function registerUser(firstName: string, lastName: string, email: string, password: string, userRole: string) {
    const response = await axios.post(apiEndpoint + '/register', 
        {
            'firstName': firstName,
            'lastName': lastName,
            'email': email,
            'password': password,
            'userRole': userRole
        }
    );

    return response.data;
}

export async function loginUser(email: string, password: string) {
    try {
        const response = await axios.post<LoginResponseDTO>(apiEndpoint + '/login',
            {
                'email': email,
                'password': password
            }
        );

        if (response.status === 200)
            return response.data as LoginResponseDTO;

        throw new Error(response.data.accessToken);
    }
    
    catch (error: any) {
        throw new Error(error.response.data.accessToken);
    }
}