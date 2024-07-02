import { ReactNode } from "react";

export type ModalContextType = {
    modalStatus: boolean;
    setModalStatus: (newStatus: boolean) => void;
    userId: number;
    setUserId: (newId: number) => void;
    removeUser: (userId: number) => void;
}

export type ModalContextProviderType = {
    modalContext: ModalContextType;
    children: ReactNode;
}