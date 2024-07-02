import { vi, expect, test } from 'vitest';
import { fireEvent, render, screen } from '@testing-library/react';
import '@testing-library/jest-dom';
import { DeleteUserModal } from '../modals/DeleteUserModal';
import { ModalContextProvider } from '../contexts/ModalContext';

test('test modal rendering', () => {
    render(
        <ModalContextProvider
            modalContext={{
                modalStatus: true,
                setModalStatus: vi.fn(),
                userId: -1,
                setUserId: vi.fn(),
                removeUser: vi.fn(),
            }}
        >
            <DeleteUserModal />
        </ModalContextProvider>,
    );

    const modalOverlay = screen.getByTestId('modal-overlay-test');
    const modalCard = screen.getByTestId('modal-card-test');

    expect(modalOverlay).toBeInTheDocument();
    expect(modalCard).toBeInTheDocument();
});

test('test modal click yes button', () => {
    const mockSetModalStatus = vi.fn();
    const mockSetUserId = vi.fn();
    const mockRemoveUser = vi.fn();

    render(
        <ModalContextProvider
            modalContext={{
                modalStatus: true,
                setModalStatus: mockSetModalStatus,
                userId: -1,
                setUserId: mockSetUserId,
                removeUser: mockRemoveUser,
            }}
        >
            <DeleteUserModal />
        </ModalContextProvider>,
    );

    const yesButton = screen.getByTestId('yes-button');

    fireEvent.click(yesButton);

    expect(mockSetModalStatus.call.length).toEqual(1);
});

test('test modal click no button', () => {
    const mockSetModalStatus = vi.fn();
    const mockSetUserId = vi.fn();
    const mockRemoveUser = vi.fn();

    render(
        <ModalContextProvider
            modalContext={{
                modalStatus: true,
                setModalStatus: mockSetModalStatus,
                userId: -1,
                setUserId: mockSetUserId,
                removeUser: mockRemoveUser,
            }}
        >
            <DeleteUserModal />
        </ModalContextProvider>,
    );

    const noButton = screen.getByTestId('no-button');

    fireEvent.click(noButton);

    expect(mockSetModalStatus.call.length).toEqual(1);
});

test('test modal click modal overlay', () => {
    const mockSetModalStatus = vi.fn();
    const mockSetUserId = vi.fn();
    const mockRemoveUser = vi.fn();

    render(
        <ModalContextProvider
            modalContext={{
                modalStatus: true,
                setModalStatus: mockSetModalStatus,
                userId: -1,
                setUserId: mockSetUserId,
                removeUser: mockRemoveUser,
            }}
        >
            <DeleteUserModal />
        </ModalContextProvider>,
    );

    const modalOverlay = screen.getByTestId('modal-overlay-test');

    fireEvent.click(modalOverlay);

    expect(mockSetModalStatus.call.length).toEqual(1);
});

test('test modal display', () => {
    const mockSetModalStatus = vi.fn();
    const mockSetUserId = vi.fn();
    const mockRemoveUser = vi.fn();

    render(
        <ModalContextProvider
            modalContext={{
                modalStatus: false,
                setModalStatus: mockSetModalStatus,
                userId: -1,
                setUserId: mockSetUserId,
                removeUser: mockRemoveUser,
            }}
        >
            <DeleteUserModal />
        </ModalContextProvider>,
    );

    const modalOverlay = screen.queryByTestId('modal-overlay-test');

    expect(modalOverlay).toBeNull();
});
