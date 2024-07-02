import { User } from "../models/user";

export type UserFormType = {
    firstNameInput: React.RefObject<HTMLInputElement>;
    lastNameInput: React.RefObject<HTMLInputElement>;
    urlInput: React.RefObject<HTMLInputElement>;
    ageInput: React.RefObject<HTMLInputElement>;
    givenUser?: User;
};