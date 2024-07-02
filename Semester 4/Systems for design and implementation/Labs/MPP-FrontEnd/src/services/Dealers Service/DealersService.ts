import axios, { AxiosResponse } from "axios";
import { endPointUrl } from "../config";
import { UserDTO } from "../../types/UserDTO.types";
import { convertDtoToUser } from "../Users Service/UsersService";

const apiEndPoint = endPointUrl + "/api/car-dealers";

export async function getDealersPage(requiredPage: number, pageSize: number) {
    const response = await axios.get<UserDTO[]>(apiEndPoint + '/getPage?page=' + requiredPage + "&size=" + pageSize);

    return response.data;
}

export async function getDealersPageFilteredByName(requiredPage: number, pageSize: number, dealerName: string) {
    let response: AxiosResponse<UserDTO[]>;
    if (!dealerName || dealerName.trim() === '')
        response = await axios.get<UserDTO[]>(apiEndPoint + '/getPage?page=' + requiredPage + "&size=" + pageSize);
    
    else response = await axios.get<UserDTO[]>(apiEndPoint + '/getPageByName?page=' + requiredPage + "&size=" + pageSize + "&name=" + dealerName);

    return response.data;
}

export async function getDealersCountByName(dealerName: string) {
    let response: AxiosResponse<number>; 

    if (!dealerName || dealerName.trim() === '')
        response = await axios.get<number>(apiEndPoint + '/getCount');

    else response = await axios.get<number>(apiEndPoint + '/getCountByName?name=' + dealerName);

    return response.data;
}

export async function getDealerById(dealerId: string) {
    const response = await axios.get<UserDTO>(apiEndPoint + '/getDealer/' + dealerId);

    return convertDtoToUser(response.data);
}