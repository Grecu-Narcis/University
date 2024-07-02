export type ButtonProps = {
    type: 'button' | 'submit' | 'reset' | undefined;
    className?: string;
    onClick?: (event?: any) => void;
    buttonMessage: string;
    backgroundColor?: string;
    textColor?: string;
    margin?: string;
    data_test_id?: string;
}