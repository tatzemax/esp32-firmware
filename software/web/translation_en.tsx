/** @jsxImportSource preact */
import { h } from "preact";
import * as options from "./src/options";
import { __ } from "./src/ts/translation";
let x = {
    "main": {
        "title": `${options.PRODUCT_NAME} Web Interface`,
        "navbar_login": "Sign In",
        "content_login": "Sign In",
        "login_username": "Username",
        "login_password": "Password",
        "login_button": "Sign In",
        "navbar_status": "Status",
        "reboot_title": "Reboot to apply configuration",
        "reboot_content": /*SFN*/ (name: string) => `The changed ${name} will only be applied after rebooting. Reboot now?`/*NF*/,
        "abort": "Abort",
        "reboot": "Reboot"
    },
    "component": {
        "config_form": {
            "save": "Save",
            "reset": "Reset"
        },
        "input_password": {
            "to_be_cleared": "Will be cleared on save.",
            "unchanged": "Unchanged",
            "required": "Required",
            "not_set": "Unset",
            "capslock_enabled": "Caps lock is enabled"
        },
        "ip_configuration": {
            "ip_configuration": "IP configuration",
            "dhcp": "Automatic (DHCP)",
            "static": "Static",

            "static_ip": "IP address",
            "subnet": "Subnet mask",
            "subnet_placeholder": "Select...",
            "gateway": "Gateway",
            "dns": "DNS server",
            "dns2": "Alternative DNS server",
            "dns2_muted": "optional",
            "static_ip_invalid": "The IP address must have four groups between 0 and 255 separated with a dot. For example 10.0.0.2",
            "gateway_invalid": "The gateway IP must have four groups between 0 and 255 separated with a dot. For example 10.0.0.1",
            "dns_invalid": "The DNS server IP must have four groups between 0 and 255 separated with a dot. For example 10.0.0.1, or be empty.",
            "dns2_invalid": "The alternative DNS server IP must have four groups between 0 and 255 separated with a dot. For example 10.0.0.1, or be empty.",
            "gateway_out_of_subnet": "Gateway address not in the configured subnet",
            "subnet_captures_prefix": "Specified IP address and subnet mask not allowed: Would capture ",
            "subnet_captures_suffix": ".",
            "ip_is_broadcast": "IP-address must not be the broadcast address!",
            "ip_is_network": "IP-address must not be the network address!",
            "wifi_ap": "the WiFi access point",
            "wifi_sta": "the WiFi connection",
            "ethernet": "the Ethernet connection",
            "wireguard": "the WireGuard connection",
            "remote_access": "the remote access"
        },
        "collapsed_section": {
            "heading": "Details",
            "show": "Show",
            "hide": "Hide"
        },
        "input_text": {
            "min_only": /*SFN*/ (min: string) => `At least ${min} characters required`/*NF*/,
            "max_only": /*SFN*/ (max: string) => `At most ${max} characters allowed`/*NF*/,
            "min_max": /*SFN*/ (min: string, max: string) => `At least ${min} characters required, but at most ${max} characters allowed`/*NF*/,
            "required": "Field must not be empty"
        },
        "input_number": {
            "min_only": /*SFN*/ (min: string, unit: string) => `At least ${min} ${unit} required`/*NF*/,
            "max_only": /*SFN*/ (max: string, unit: string) => `At most ${max} ${unit} allowed`/*NF*/,
            "min_max": /*SFN*/ (min: string, max: string, unit: string) => `At least ${min} ${unit} required, but at most ${max} ${unit} allowed`/*NF*/,
            "required": "Field must not be empty"
        },
        "input_any_float": {
            "min_only": /*SFN*/ (min: number) => `At least ${min} required`/*NF*/,
            "max_only": /*SFN*/ (max: number) => `At most ${max} allowed`/*NF*/,
            "min_max": /*SFN*/ (min: number, max: number) => `At least ${min} required, but at most ${max} allowed`/*NF*/
        },
        "input_file": {
            "uploading": "uploading..."
        },
        "input_host": {
            "invalid_feedback": "Hostname or IP address is invalid"
        },
        "table": {
            "abort": "Discard",
            "add": "Add",
            "apply": "Apply"
        },
        "remote_close_button": {
            "close": "Close remote access"
        },
        "debug_logger": {
            "loading_debug_report": "Loading debug report",
            "loading_debug_report_failed": "Loading debug report failed",
            "loading_event_log": "Loading event log",
            "loading_event_log_failed": "Loading event log failed",
            "tab_close_warning": /*SFN*/ (debug_module: string) => `${debug_module} capture will be aborted if this tab is closed.`/*NF*/,
            "starting_debug": /*SFN*/ (debug_module: string) => `Starting to record ${debug_module} log`/*NF*/,
            "starting_debug_failed": /*SFN*/ (debug_module: string) => `Starting to record ${debug_module} log failed`/*NF*/,
            "debug_running": "Recording. Do not close tab!",
            "debug_stop_failed": /*SFN*/ (debug_module: string) => `Stopping to record ${debug_module} log failed`/*NF*/,
            "debug_stopped": /*SFN*/ (debug_module: string) => `Stupped recording ${debug_module} log`/*NF*/,
            "debug_done": "Done.",
            "debug_start": "Start",
            "debug_stop": "Stop + Download"
        }
    },
    "util": {
        "reboot_title": "Rebooting...",
        "reboot_text": "The web interface will be reloaded automatically after the restart.",
        "event_connection_lost_title": <>{__("branding.device")} connection lost!</>,
        "event_connection_lost": "Connection will be reestablished...",

        "upload_abort": "Upload aborted",
        "upload_error": "Upload error",
        "upload_timeout": "Upload timed out",
        "download_abort": "Download aborted",
        "download_error": "Download error",
        "download_timeout": "Download timed out",
        "not_yet_known": "Not yet known"
    },
    "reset": {
        "reset_modal": "Reset Config",
        "reset_modal_body": "Really reset the configuration?",
        "reset_modal_body_prefix": "Really reset ",
        "reset_modal_body_postfix": " ?",
        "reset_modal_abort": "Abort",
        "reset_modal_confirm": "Reset"
    },
    "days": "days",
    "day": "day",
    "today": "Today",
    "tomorrow": "Tomorrow",
    "select": "Select...",
    "branding": {
        "device": null,
        "the": "the",
        "The": "The",
        "this": "this",
        "This": "This",
        "to_the": "to the",
        "from_the": "from the"
    },
    "device": <>{__("branding.device")}</>,
    "the_device": <>{__("branding.the")} {__("branding.device")}</>,
    "The_device": <>{__("branding.The")} {__("branding.device")}</>,
    "this_device": <>{__("branding.this")} {__("branding.device")}</>,
    "This_device": <>{__("branding.This")} {__("branding.device")}</>,
    "to_the_device": <>{__("branding.to_the")} {__("branding.device")}</>,
    "from_the_device": <>{__("branding.from_the")} {__("branding.device")}</>
}
