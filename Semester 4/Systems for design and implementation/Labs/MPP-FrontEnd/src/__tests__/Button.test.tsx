import { expect, test } from 'vitest';
import { render, screen } from '@testing-library/react';
import '@testing-library/jest-dom';
import { Button } from '../shared/components/button/Button';

test('test button rendering without extra class', () => {
    render(<Button type='button' buttonMessage='Test button' />);

    const renderedButton = screen.getByTestId('button-test-id');
    expect(renderedButton).toBeInTheDocument();
});

test('test button rendering with extra class', () => {
    render(<Button type='button' buttonMessage='Test button' className='demo-class' />);

    const renderedButton = screen.getByTestId('button-test-id');
    expect(renderedButton).toBeInTheDocument();
});
