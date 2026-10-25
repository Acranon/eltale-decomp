def apply(config, args):
    config["baseimg"] = "baserom.jp.z64"
    config["myimg"] = "build/eltale.z64"
    config["mapfile"] = "build/eltale.map"
    config["source_directories"] = ["src", "include"]
    config["make_command"] = ["ninja"]
    config["arch"] = "mips"
